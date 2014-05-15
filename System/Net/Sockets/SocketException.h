#pragma once
#include <System/Exception/SystemException.h>
namespace System {
	namespace Net {
		namespace Sockets {
			class SocketException : public SystemException{
				SocketException();
				SocketException(int code);
			};
		}
	}
}