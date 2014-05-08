#ifdef AAAA
#include "IPEndPoint.h"
namespace System {
	namespace Net {
		IPEndPoint* IPEndPoint::Any = new IPEndPoint(IPAddress::Any, 0);
		IPEndPoint* IPEndPoint::IPv6Any = new IPEndPoint(IPAddress::IPv6Any, 0);
		AddressFamily IPEndPoint::getAddressFamily(){
			return this->m_Address->AddressFamily;
		}
		IPAddress* IPEndPoint::getAddress()
		{
			return this->m_Address;
		}
		void IPEndPoint::setAddress(IPAddress* value)
		{
			this->m_Address = value;
		}
		int IPEndPoint::getPort()
		{
			return this->m_Port;
		}
		void IPEndPoint::setPort(int value)
		{
			if (!ValidationHelper::ValidateTcpPort(value)) {
				throw new ArgumentOutOfRangeException(new String("value"));
			}
			this->m_Port = value;
		}
		IPEndPoint::IPEndPoint(long address, int port)
		{
			AnyPort = 0;
			MaxPort = 65535;
			MinPort = 0;
			if (!ValidationHelper::ValidateTcpPort(port)) {
				throw new ArgumentOutOfRangeException(new String("port"));
			}
			this->m_Port = port;
			this->m_Address = new IPAddress(address);
		}
		IPEndPoint::IPEndPoint(IPAddress* address, int port)
		{
			if (address == null) {
				throw new ArgumentNullException(new String("address"));
			}
			if (!ValidationHelper::ValidateTcpPort(port)) {
				throw new ArgumentOutOfRangeException(new String("port"));
			}
			this->m_Port = port;
			this->m_Address = address;
		}
		String* IPEndPoint::ToString()
		{
			String* format;
			if (this->m_Address->AddressFamily == AddressFamily::InterNetworkV6) {
				format = new String("[{0}]:{1}");
			}
			else {
				format = new String("{0}:{1}");
			}
			return String::Format(format, this->m_Address->ToString(), new String(this->getPort()));
		}
		SocketAddress* IPEndPoint::Serialize()
		{
			return new SocketAddress(this->getAddress(), this->getPort());
		}
		EndPoint* IPEndPoint::Create(SocketAddress* socketAddress)
		{
			if (socketAddress->Family != this->getAddressFamily()) {
				String* arg_4F_0 = new String("net_InvalidAddressFamily");
				Array<Object>* array = new Array<Object>(3);
				array->SetData(0, BOX<AddressFamily>(socketAddress->Family)->ToString());
				array->SetData(1, EndPoint::GetType()->FullName);
				array->SetData(2, BOX<AddressFamily>(this->getAddressFamily())->ToString());
				throw new ArgumentException(new String("socketAddress"));
			}
			if (socketAddress->Size < 8) {
				String* arg_91_0 = new String("net_InvalidSocketAddressSize");
				Array<Object>* array2 = new Array<Object>(2);
				array2->SetData(0, socketAddress->GetType()->FullName);
				array2->SetData(1, EndPoint::GetType()->FullName);
				throw new ArgumentException(new String("socketAddress"));
			}
			return socketAddress->GetIPEndPoint();
		}
		bool IPEndPoint::Equals(Object* comparand)
		{
			return is_inst_of<IPEndPoint*>(comparand) && (IPEndPoint*)(comparand)->m_Address->Equals(this->m_Address) && (IPEndPoint*)(comparand)->m_Port == this->m_Port;
		}
		int IPEndPoint::GetHashCode()
		{
			return this->m_Address->GetHashCode() ^ this->m_Port;
		}
		IPEndPoint* IPEndPoint::Snapshot()
		{
			return new IPEndPoint(this->getAddress()->Snapshot(), this->getPort());
		}

	}
}
#endif