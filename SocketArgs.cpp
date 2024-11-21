#include "SocketArgs.h"
#include <cstring> 

SocketArgs::SocketArgs()
    : bufferSize(0), buffer(nullptr) {} 

SocketArgs::SocketArgs(size_t bufferSize)
    : bufferSize(bufferSize), buffer(new uint8_t[bufferSize]) {}

SocketArgs::~SocketArgs() {
    delete[] buffer;
}

