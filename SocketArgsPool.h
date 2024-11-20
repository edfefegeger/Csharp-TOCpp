#ifndef SOCKETARGPOOL_HPP
#define SOCKETARGPOOL_HPP

#include "SocketArgs.h"

class SocketArgsPool {
public:
    static SocketArgs* GetReceiveArg();
    static SocketArgs* GetSendArg();

private:
    static std::vector<SocketArgs> SocketReceiveArgs;
    static std::vector<SocketArgs> SocketSendArgs;
};

#endif // SOCKETARGPOOL_HPP
