#ifdef AAAA
#pragma once
#include <System/System.h>
#include "../Net/Sockets/AddressFamily.h"
#include "SocketException.h"
#include "SocketError.h"
#include <System/SystemException/ArgumentException/ArgumentOutOfRangeException.h>
#include <System/Exception/SystemException/ArgumentException/ArgumentNullException.h>
#include <System/SystemException/ArgumentException.h>
#include "Sockets/Socket.h"
#include "SocketAddress.h"
#include "UnsafeNclNativeMethods.h"
#include "IntPtr.h"
#include "IPv6AddressHelper.h"
#include "NumberStyles.h"
#include "FormatException.h"
#include "IPv4AddressHelper.h"
#include <System/Text/StringBuilder.h>
#include "IFormatProvider.h"
#include "CultureInfo.h"
#include "UIntPtr.h"
#include "StringComparer.h"
#include "InternalException.h"

using namespace System;
using namespace System::Net::Sockets;
using namespace System::Runtime;
using namespace System::Globalization;
using namespace System::Text;
namespace System {
	namespace Net {
		//Attribute: Serializable*
		class IPAddress : public virtual Object{
			public:
				long LoopbackMask;
			public:
				int IPv4AddressBytes;
			public:
				int IPv6AddressBytes;
			public:
				int NumberOfLabels;
			public:
			static IPAddress* Any;
			public:
			static IPAddress* Loopback;
			public:
			static IPAddress* Broadcast;
			public:
			static IPAddress* None;
			public:
				long m_Address;
			//Attribute: NonSerialized*
			public:
				String* m_ToString;
			public:
			static IPAddress* IPv6Any;
			public:
			static IPAddress* IPv6Loopback;
			public:
			static IPAddress* IPv6None;
			private:
				AddressFamily m_Family;
			private:
				Array<ushort>* m_Numbers;
			private:
				long m_ScopeId;
			private:
				int m_HashCode;
			public:
				long getAddress();
			public:
				void setAddress(long value);
			public:
				AddressFamily getAddressFamily();
				//Ignored empty method declaration
			public:
				long getScopeId();
			public:
				void setScopeId(long value);
			public:
				bool getIsBroadcast();
				//Ignored empty method declaration
			public:
				bool getIsIPv6Multicast();
				//Ignored empty method declaration
			public:
				bool getIsIPv6LinkLocal();
				//Ignored empty method declaration
			public:
				bool getIsIPv6SiteLocal();
				//Ignored empty method declaration
			public:
				bool getIsIPv6Teredo();
				//Ignored empty method declaration
			public:
				bool getIsIPv4MappedToIPv6();
				//Ignored empty method declaration
			public:
				IPAddress(long newAddress);
			public:
				IPAddress(Array<char>* address, long scopeid);
			public:
				IPAddress(Array<char>* address);
			public:
				IPAddress(int newAddress);
			public:
			static bool TryParse(String* ipString, IPAddress* address);
			//Attribute: TargetedPatchingOptOut*(new String("Performance critical to inline this type of method across NGen image boundaries"))
			public:
			static IPAddress* Parse(String* ipString);
			private:
			static IPAddress* InternalParse(String* ipString, bool tryParse);
			public:
				Array<char>* GetAddressBytes();
			public:
			virtual String* ToString();
			public:
			static long HostToNetworkOrder(long host);
			public:
			static int HostToNetworkOrder(int host);
			public:
			static short HostToNetworkOrder(short host);
			//Attribute: TargetedPatchingOptOut*(new String("Performance critical to inline this type of method across NGen image boundaries"))
			public:
			static long NetworkToHostOrder(long network);
			//Attribute: TargetedPatchingOptOut*(new String("Performance critical to inline this type of method across NGen image boundaries"))
			public:
			static int NetworkToHostOrder(int network);
			//Attribute: TargetedPatchingOptOut*(new String("Performance critical to inline this type of method across NGen image boundaries"))
			public:
			static short NetworkToHostOrder(short network);
			public:
			static bool IsLoopback(IPAddress* address);
			public:
				bool Equals(Object* comparandObj, bool compareScopeId);
			//Attribute: TargetedPatchingOptOut*(new String("Performance critical to inline this type of method across NGen image boundaries"))
			public:
			virtual bool Equals(Object* comparand);
			public:
			virtual int GetHashCode();
			public:
				IPAddress* Snapshot();
			public:
				IPAddress* MapToIPv6();
			public:
				IPAddress* MapToIPv4();
			private:
				IPAddress(Array<ushort>* address, uint scopeid);
			private:
				static IPAddress();
		};
	}
}
#endif