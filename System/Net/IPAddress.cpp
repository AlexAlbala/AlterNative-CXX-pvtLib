#ifdef A
#include "IPAddress.h"
namespace System {
	namespace Net {
		IPAddress* IPAddress::Any = new IPAddress(0);
		IPAddress* IPAddress::Loopback = new IPAddress(16777343);
		IPAddress* IPAddress::Broadcast = new IPAddress((long)((ulong)(-1)));
		IPAddress* IPAddress::None = IPAddress::Broadcast;
		IPAddress* IPAddress::IPv6Any;
		IPAddress* IPAddress::IPv6Loopback;
		IPAddress* IPAddress::IPv6None;
		long IPAddress::getAddress(){
			if (this->m_Family == AddressFamily::InterNetworkV6){
				throw new SocketException(SocketError::OperationNotSupported);
			}
			return this->m_Address;
		}
		void IPAddress::setAddress(long value)
		{
			if (this->m_Family == AddressFamily::InterNetworkV6) {
				throw new SocketException(SocketError::OperationNotSupported);
			}
			if (this->m_Address != value) {
				this->m_ToString = null;
				this->m_Address = value;
			}
		}
		AddressFamily IPAddress::getAddressFamily()
		{
			return this->m_Family;
		}
		long IPAddress::getScopeId()
		{
			if (this->m_Family == AddressFamily::InterNetwork) {
				throw new SocketException(SocketError::OperationNotSupported);
			}
			return this->m_ScopeId;
		}
		void IPAddress::setScopeId(long value)
		{
			if (this->m_Family == AddressFamily::InterNetwork) {
				throw new SocketException(SocketError::OperationNotSupported);
			}
			if (value < 0L || value > (long)((ulong)(-1))) {
				throw new ArgumentOutOfRangeException(new String("value"));
			}
			if (this->m_ScopeId != value) {
				this->m_Address = value;
				this->m_ScopeId = value;
			}
		}
		bool IPAddress::getIsBroadcast()
		{
			return this->m_Family != AddressFamily::InterNetworkV6 && this->m_Address == IPAddress::Broadcast->m_Address;
		}
		bool IPAddress::getIsIPv6Multicast()
		{
			return this->m_Family == AddressFamily::InterNetworkV6 && (*this->m_Numbers)[0] & 65280 == 65280;
		}
		bool IPAddress::getIsIPv6LinkLocal()
		{
			return this->m_Family == AddressFamily::InterNetworkV6 && (*this->m_Numbers)[0] & 65472 == 65152;
		}
		bool IPAddress::getIsIPv6SiteLocal()
		{
			return this->m_Family == AddressFamily::InterNetworkV6 && (*this->m_Numbers)[0] & 65472 == 65216;
		}
		bool IPAddress::getIsIPv6Teredo()
		{
			return this->m_Family == AddressFamily::InterNetworkV6 && (*this->m_Numbers)[0] == 8193 && (*this->m_Numbers)[1] == 0;
		}
		bool IPAddress::getIsIPv4MappedToIPv6()
		{
			if (this->getAddressFamily() != AddressFamily::InterNetworkV6) {
				return false;
			}
			for (int i = 0; i < 5; i += 1) {
				if ((*this->m_Numbers)[i] != 0) {
					return false;
				}
			}
			return (*this->m_Numbers)[5] == 65535;
		}
		IPAddress::IPAddress(long newAddress)
		{
			m_Numbers = new Array<ushort>(8);
			m_Family = AddressFamily::InterNetwork;
			NumberOfLabels = 8;
			IPv6AddressBytes = 16;
			IPv4AddressBytes = 4;
			LoopbackMask = 255L;
			if (newAddress < 0L || newAddress > (long)((ulong)(-1))) {
				throw new ArgumentOutOfRangeException(new String("newAddress"));
			}
			this->m_Address = newAddress;
		}
		IPAddress::IPAddress(Array<char>* address, long scopeid)
		{
			if (address == null) {
				throw new ArgumentNullException(new String("address"));
			}
			if (address->Length != 16) {
				throw new ArgumentException(new String("address"));
			}
			this->m_Family = AddressFamily::InterNetworkV6;
			for (int i = 0; i < 8; i += 1) {
				this->m_Numbers->SetData(i, (ushort)((int)((*address)[i * 2]) * 256 + (int)((*address)[i * 2 + 1])));
			}
			if (scopeid < 0L || scopeid > (long)((ulong)(-1))) {
				throw new ArgumentOutOfRangeException(new String("scopeid"));
			}
			this->m_ScopeId = scopeid;
		}
		IPAddress::IPAddress(Array<char>* address)
		{
			if (address == null) {
				throw new ArgumentNullException(new String("address"));
			}
			if (address->Length != 4 && address->Length != 16) {
				throw new ArgumentException(new String("address"));
			}
			if (address->Length == 4) {
				this->m_Family = AddressFamily::InterNetwork;
				this->m_Address = (long)((int)((*address)[3]) << 24 | (int)((*address)[2]) << 16 | (int)((*address)[1]) << 8 | (int)((*address)[0])) & (long)((ulong)(-1));
				return;
			}
			this->m_Family = AddressFamily::InterNetworkV6;
			for (int i = 0; i < 8; i += 1) {
				this->m_Numbers->SetData(i, (ushort)((int)((*address)[i * 2]) * 256 + (int)((*address)[i * 2 + 1])));
			}
		}
		IPAddress::IPAddress(int newAddress)
		{
			this->m_Address = (long)(newAddress) & (long)((ulong)(-1));
		}
		bool IPAddress::TryParse(String* ipString, IPAddress* address)
		{
			address = IPAddress::InternalParse(ipString, true);
			return address != null;
		}
		//Attribute: TargetedPatchingOptOut*(new String("Performance critical to inline this type of method across NGen image boundaries"))
		IPAddress* IPAddress::Parse(String* ipString){
			return IPAddress::InternalParse(ipString, false);
		}
		IPAddress* IPAddress::InternalParse(String* ipString, bool tryParse)
		{
			if (ipString == null) {
				if (tryParse) {
					return null;
				}
				throw new ArgumentNullException(new String("ipString"));
			}
			else {
				if (ipString->IndexOf(':') != -1) {
					SocketException* innerException;
					if (Socket::OSSupportsIPv6) {
						Array<char>* array = new Array<char>(16);
						SocketAddress* socketAddress = new SocketAddress(AddressFamily::InterNetworkV6, 28);
						if (UnsafeNclNativeMethods::OSSOCK::WSAStringToAddress(ipString, AddressFamily::InterNetworkV6, IntPtr::Zero, socketAddress->m_Buffer, socketAddress->m_Size) == SocketError::Success) {
							for (int i = 0; i < 16; i += 1) {
								array->SetData(i, (*socketAddress)[i + 8]);
							}
							long scopeid = (long)((int)((*socketAddress)[27]) << 24 + (int)((*socketAddress)[26]) << 16 + (int)((*socketAddress)[25]) << 8 + (int)((*socketAddress)[24]));
							return new IPAddress(array, scopeid);
						}
						if (tryParse) {
							return null;
						}
						innerException = new SocketException();
					}
					else {
						int start = 0;
						if ((*ipString)[0] != '[') {
							ipString += BOX<char>(']');
						}
						else {
							start = 1;
						}
						int length = ipString->getLength();
						//Fixed statement ignored
						char* name = *ipString;
						//Start fixed block
						 if (IPv6AddressHelper::IsValidStrict(name, start, length) || length != ipString->getLength()){
							Array<ushort>* array2 = new Array<ushort>(8);
							String* text = null;
							//Fixed statement ignored
							ushort* ptr = *array2;
							//Start fixed block
							 IPv6AddressHelper::Parse(ipString, ptr, 0, text);
							//End fixed block
							IPAddress* result;
							if (text == null || text->getLength() == 0){
								result = new IPAddress(array2, 0u);
							}
							else {
								text = text->Substring(1);
								uint scopeid2;
								if (!uint::TryParse(text, NumberStyles::None, null, scopeid2)) {
									goto IL_193;
								}
								result = new IPAddress(array2, scopeid2);
							}
							return result;
						}
						IL_193:;
						//End fixed block
						if (tryParse){
							return null;
						}
						innerException = new SocketException(SocketError::InvalidArgument);
					}
					throw new FormatException(SR::GetString(new String("dns_bad_ip_address")), innerException);
				}
				Socket::InitializeSockets();
				int length2 = ipString->getLength();
				long num;
				//Fixed statement ignored
				char* name2 = *ipString;
				//Start fixed block
				 num = IPv4AddressHelper::ParseNonCanonical(name2, 0, length2, true);
				//End fixed block
				if (num != -1L && length2 == ipString->getLength()){
					num = num & 255L << 24 | num & 65280L << 8 | num & 16711680L >> 8 | num & (long)((ulong)(-16777216)) >> 24;
					return new IPAddress(num);
				}
				if (tryParse) {
					return null;
				}
				throw new FormatException(SR::GetString(new String("dns_bad_ip_address")));
			}
		}
		Array<char>* IPAddress::GetAddressBytes()
		{
			Array<char>* array;
			if (this->m_Family == AddressFamily::InterNetworkV6) {
				array = new Array<char>(16);
				int num = 0;
				for (int i = 0; i < 8; i += 1) {
					array->SetData(num++, (char)((*this->m_Numbers)[i] >> 8 & 255));
					array->SetData(num++, (char)((*this->m_Numbers)[i] & 255));
				}
			}
			else {
				array = new Array<char>(4);
				array->SetData(0, (char)(this->m_Address));
				array->SetData(1, (char)(this->m_Address >> 8));
				array->SetData(2, (char)(this->m_Address >> 16));
				array->SetData(3, (char)(this->m_Address >> 24));
			}
			return array;
		}
		String* IPAddress::ToString()
		{
			if (this->m_ToString == null) {
				/*if (this->m_Family == AddressFamily::InterNetworkV6) {
					int capacity = 256;
					StringBuilder* stringBuilder = new StringBuilder(capacity);
					if (Socket::OSSupportsIPv6) {
						SocketAddress* socketAddress = new SocketAddress(AddressFamily::InterNetworkV6, 28);
						int num = 8;
						for (int i = 0; i < 8; i += 1) {
							socketAddress->SetData(num++, (char)((*this->m_Numbers)[i] >> 8));
							socketAddress->SetData(num++, (char)((*this->m_Numbers)[i]));
						}
						if (this->m_ScopeId > 0L) {
							socketAddress->SetData(24, (char)(this->m_ScopeId));
							socketAddress->SetData(25, (char)(this->m_ScopeId >> 8));
							socketAddress->SetData(26, (char)(this->m_ScopeId >> 16));
							socketAddress->SetData(27, (char)(this->m_ScopeId >> 24));
						}
						SocketError socketError = UnsafeNclNativeMethods::OSSOCK::WSAAddressToString(socketAddress->m_Buffer, socketAddress->m_Size, IntPtr::Zero, stringBuilder, capacity);
						if (socketError != SocketError::Success) {
							throw new SocketException();
						}
					}
					else {
						IFormatProvider* arg_1C9_0 = CultureInfo::InvariantCulture;
						String* arg_1C9_1 = new String("{0:x4}:{1:x4}:{2:x4}:{3:x4}:{4:x4}:{5:x4}:{6}.{7}.{8}.{9}");
						Array<Object>* array = new Array<Object>(10);
						array->SetData(0, BOX<ushort>((*this->m_Numbers)[0]));
						array->SetData(1, BOX<ushort>((*this->m_Numbers)[1]));
						array->SetData(2, BOX<ushort>((*this->m_Numbers)[2]));
						array->SetData(3, BOX<ushort>((*this->m_Numbers)[3]));
						array->SetData(4, BOX<ushort>((*this->m_Numbers)[4]));
						array->SetData(5, BOX<ushort>((*this->m_Numbers)[5]));
						array->SetData(6, BOX<int>((*this->m_Numbers)[6] >> 8 & 255));
						array->SetData(7, BOX<int>((int)((*this->m_Numbers)[6] & 255)));
						array->SetData(8, BOX<int>((*this->m_Numbers)[7] >> 8 & 255));
						array->SetData(9, BOX<int>((int)((*this->m_Numbers)[7] & 255)));
						String* value = String::Format(arg_1C9_0, arg_1C9_1, array);
						stringBuilder->Append(value);
						if (this->m_ScopeId != 0L) {
							stringBuilder->Append('%')->Append((uint)(this->m_ScopeId));
						}
					}
					this->m_ToString = stringBuilder->ToString();
				}
				else {*/
					int num2 = 15;
					char* ptr_t = (char*)STACKALLOC(char[15]);
					Array<char>* ptr = new Array<char>(ptr_t, 15);

					int num3 = (int)(this->m_Address >> 24 & 255L);
					do {
						ptr->SetData((num2 -= 1), (char)(48 + num3 % 10));
						num3 /= 10;
					}
					while (num3 > 0);
					ptr->SetData((num2 -= 1), '.');
					num3 = (int)(this->m_Address >> 16 & 255L);
					do {
						ptr->SetData((num2 -= 1), (char)(48 + num3 % 10));
						num3 /= 10;
					}
					while (num3 > 0);
					ptr->SetData((num2 -= 1), '.');
					num3 = (int)(this->m_Address >> 8 & 255L);
					do {
						ptr->SetData((num2 -= 1), (char)(48 + num3 % 10));
						num3 /= 10;
					}
					while (num3 > 0);
					ptr->SetData((num2 -= 1), '.');
					num3 = (int)(this->m_Address & 255L);
					do {
						ptr->SetData((num2 -= 1), (char)(48 + num3 % 10));
						num3 /= 10;
					}
					while (num3 > 0);
					this->m_ToString = new String(ptr, num2, 15 - num2);
				//}
			}
			return this->m_ToString;
		}
		long IPAddress::HostToNetworkOrder(long host)
		{
			return (long)(IPAddress::HostToNetworkOrder((int)(host))) & (long)((ulong)(-1)) << 32 | (long)(IPAddress::HostToNetworkOrder((int)(host >> 32))) & (long)((ulong)(-1));
		}
		int IPAddress::HostToNetworkOrder(int host)
		{
			return (int)(IPAddress::HostToNetworkOrder((short)(host))) & 65535 << 16 | (int)(IPAddress::HostToNetworkOrder((short)(host >> 16))) & 65535;
		}
		short IPAddress::HostToNetworkOrder(short host)
		{
			return (short)((int)(host & 255) << 8 | host >> 8 & 255);
		}
		//Attribute: TargetedPatchingOptOut*(new String("Performance critical to inline this type of method across NGen image boundaries"))
		long IPAddress::NetworkToHostOrder(long network){
			return IPAddress::HostToNetworkOrder(network);
		}
		//Attribute: TargetedPatchingOptOut*(new String("Performance critical to inline this type of method across NGen image boundaries"))
		int IPAddress::NetworkToHostOrder(int network){
			return IPAddress::HostToNetworkOrder(network);
		}
		//Attribute: TargetedPatchingOptOut*(new String("Performance critical to inline this type of method across NGen image boundaries"))
		short IPAddress::NetworkToHostOrder(short network){
			return IPAddress::HostToNetworkOrder(network);
		}
		bool IPAddress::IsLoopback(IPAddress* address)
		{
			if (address == null) {
				throw new ArgumentNullException(new String("address"));
			}
			if (address->m_Family == AddressFamily::InterNetworkV6) {
				return address->Equals(IPAddress::IPv6Loopback);
			}
			return address->m_Address & 255L == IPAddress::Loopback->m_Address & 255L;
		}
		bool IPAddress::Equals(Object* comparandObj, bool compareScopeId)
		{
			IPAddress* iPAddress = as_cast<IPAddress*>(comparandObj);
			if (iPAddress == null) {
				return false;
			}
			if (this->m_Family != iPAddress->m_Family) {
				return false;
			}
			if (this->m_Family == AddressFamily::InterNetworkV6) {
				for (int i = 0; i < 8; i += 1) {
					if (iPAddress->m_Numbers[i] != (*this->m_Numbers)[i]) {
						return false;
					}
				}
				return iPAddress->m_ScopeId == this->m_ScopeId || !compareScopeId;
			}
			return iPAddress->m_Address == this->m_Address;
		}
		//Attribute: TargetedPatchingOptOut*(new String("Performance critical to inline this type of method across NGen image boundaries"))
		bool IPAddress::Equals(Object* comparand){
			return this->Equals(comparand, true);
		}
		int IPAddress::GetHashCode()
		{
			if (this->m_Family == AddressFamily::InterNetworkV6) {
				if (this->m_HashCode == 0) {
					this->m_HashCode = StringComparer::InvariantCultureIgnoreCase->GetHashCode(this->ToString());
				}
				return this->m_HashCode;
			}
			return (int)(this->m_Address);
		}
		IPAddress* IPAddress::Snapshot()
		{
			AddressFamily family = this->m_Family;
			if (family == AddressFamily::InterNetwork) {
				return new IPAddress(this->m_Address);
			}
			if (family != AddressFamily::InterNetworkV6) {
				throw new InternalException();
			}
			return new IPAddress(this->m_Numbers, (uint)(this->m_ScopeId));
		}
		IPAddress* IPAddress::MapToIPv6()
		{
			if (this->getAddressFamily() == AddressFamily::InterNetworkV6) {
				return this;
			}
			Array<ushort>* array = new Array<ushort>(8);
			array->SetData(5, 65535);
			array->SetData(6, (ushort)(this->m_Address & 65280L >> 8 | this->m_Address & 255L << 8));
			array->SetData(7, (ushort)(this->m_Address & (long)((ulong)(-16777216)) >> 24 | this->m_Address & 16711680L >> 8));
			return new IPAddress(array, 0u);
		}
		IPAddress* IPAddress::MapToIPv4()
		{
			if (this->getAddressFamily() == AddressFamily::InterNetwork) {
				return this;
			}
			long newAddress = (long)((*this->m_Numbers)[6] & 65280 >> 8 | (int)((*this->m_Numbers)[6] & 255) << 8 | (*this->m_Numbers)[7] & 65280 >> 8 | (int)((*this->m_Numbers)[7] & 255) << 8 << 16);
			return new IPAddress(newAddress);
		}
		IPAddress::IPAddress(Array<ushort>* address, uint scopeid)
		{
			this->m_Family = AddressFamily::InterNetworkV6;
			this->m_Numbers = address;
			this->m_ScopeId = (long)((ulong)(scopeid));
		}
		IPAddress::IPAddress()
		{
			Array<char>* address = new Array<char>(16);
			IPAddress::IPv6Any = new IPAddress(address, 0L);
			Array<char>* array = new Array<char>(16);
			array->SetData(15, 1);
			IPAddress::IPv6Loopback = new IPAddress(array, 0L);
			Array<char>* address2 = new Array<char>(16);
			IPAddress::IPv6None = new IPAddress(address2, 0L);
		}

	}
}
#endif