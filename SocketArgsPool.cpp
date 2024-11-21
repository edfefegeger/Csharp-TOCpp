#include "SocketArgsPool.h"

// Определение статических переменных
SocketArgs SocketArgsPool::SocketReceiveArgs[SocketArgsPool::MaxArgs] = { SocketArgs(1024) };
SocketArgs SocketArgsPool::SocketSendArgs[SocketArgsPool::MaxArgs] = { SocketArgs(1024) };
size_t SocketArgsPool::ReceiveArgsCount = 0;
size_t SocketArgsPool::SendArgsCount = 0;
volatile bool SocketArgsPool::isLocked = false;

void SocketArgsPool::Lock() {
    while (isLocked); // Ждем, пока блокировка освободится
    isLocked = true;
}

void SocketArgsPool::Unlock() {
    isLocked = false;
}

SocketArgs* SocketArgsPool::GetReceiveArg() {
    Lock();

    for (size_t i = 0; i < ReceiveArgsCount; ++i) {
        if (!SocketReceiveArgs[i].IsInUse) {
            SocketReceiveArgs[i].IsInUse = true;
            Unlock();
            return &SocketReceiveArgs[i];
        }
    }

    if (ReceiveArgsCount < MaxArgs) {
        SocketReceiveArgs[ReceiveArgsCount] = SocketArgs(1024);
        SocketReceiveArgs[ReceiveArgsCount].IsInUse = true;
        Unlock();
        return &SocketReceiveArgs[ReceiveArgsCount++];
    }

    Unlock();
    return nullptr;
}

SocketArgs* SocketArgsPool::GetSendArg() {
    Lock();

    for (size_t i = 0; i < SendArgsCount; ++i) {
        if (!SocketSendArgs[i].IsInUse) {
            SocketSendArgs[i].IsInUse = true;
            Unlock();
            return &SocketSendArgs[i];
        }
    }

    if (SendArgsCount < MaxArgs) {
        SocketSendArgs[SendArgsCount] = SocketArgs(1024);
        SocketSendArgs[SendArgsCount].IsInUse = true;
        Unlock();
        return &SocketSendArgs[SendArgsCount++];
    }

    Unlock();
    return nullptr;
}
