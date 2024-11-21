#ifndef SOCKETARGPOOL_H
#define SOCKETARGPOOL_H

#include "SocketArgs.h"

class SocketArgsPool {
public:
    static SocketArgs* GetReceiveArg();
    static SocketArgs* GetSendArg();

private:
    static const size_t MaxArgs = 100; // ћаксимальное количество аргументов
    static SocketArgs SocketReceiveArgs[MaxArgs];
    static SocketArgs SocketSendArgs[MaxArgs];
    static size_t ReceiveArgsCount;
    static size_t SendArgsCount;

    static void Lock();
    static void Unlock();
    static volatile bool isLocked;
};

#endif // SOCKETARGPOOL_HPP
