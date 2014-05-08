#ifdef AAAA
#pragma once
#include <System/System.h>
#include "EndPoint.h"
#include "IPAddress.h"
#include "Sockets/AddressFamily.h"
#include "ValidationHelper.h"
#include <System/Exception/SystemException/ArgumentException/ArgumentOutOfRangeException.h>
#include <System/Exception/SystemException/ArgumentException/ArgumentNullException.h>
#include "SocketAddress.h"
#include <System/Exception/SystemException/ArgumentException.h>

using namespace System;
using namespace System::Net::Sockets;
namespace System {
	namespace Net {
		//Attribute: Serializable*
		class IPEndPoint : public virtual EndPoint, public virtual Object{
			public:
				int MinPort;
			public:
				int MaxPort;
			public:
				int AnyPort;
			private:
				IPAddress* m_Address;
			private:
				int m_Port;
			public:
			static IPEndPoint* Any;
			public:
			static IPEndPoint* IPv6Any;
			public:
			virtual AddressFamily getAddressFamily();
				//Ignored empty method declaration
			public:
				IPAddress* getAddress();
			public:
				void setAddress(IPAddress* value);
			public:
				int getPort();
			public:
				void setPort(int value);
			public:
				IPEndPoint(long address, int port);
			public:
				IPEndPoint(IPAddress* address, int port);
			public:
			virtual String* ToString();
			public:
			virtual SocketAddress* Serialize();
			public:
			virtual EndPoint* Create(SocketAddress* socketAddress);
			public:
			virtual bool Equals(Object* comparand);
			public:
			virtual int GetHashCode();
			public:
				IPEndPoint* Snapshot();
		};
	}
}
#endif