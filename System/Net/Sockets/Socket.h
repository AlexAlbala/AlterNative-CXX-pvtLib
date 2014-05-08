#pragma once
#include <System/IDisposable.h>
#include "ProtocolType.h"
#include <boost/asio.hpp>

using namespace boost::asio::ip;
namespace System{
	namespace Net{
		namespace Sockets {
			class Socket : public virtual IDisposable
			{
			private:
				ProtocolType pType;

				tcp::socket	tSocket;
				udp::socket uSocket;
			};
		}
	}
}