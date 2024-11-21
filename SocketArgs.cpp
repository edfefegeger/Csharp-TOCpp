#include "SocketArgs.h"
#include <cstring> // Для memcpy

SocketArgs::SocketArgs()
    : bufferSize(0), buffer(nullptr) {} // Конструктор по умолчанию

SocketArgs::SocketArgs(size_t bufferSize)
    : bufferSize(bufferSize), buffer(new uint8_t[bufferSize]) {}

SocketArgs::~SocketArgs() {
    delete[] buffer;
}

