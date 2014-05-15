#include "SocketException.h"

namespace System {
	namespace Net {
		namespace Sockets {

			SocketException::SocketException() : SystemException(){
			}

			SocketException::SocketException(int code) : SystemException(new String(code)){
			}
		
		}
	}
}