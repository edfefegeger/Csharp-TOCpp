#ifndef SOCKETARGS_H
#define SOCKETARGS_H

#include <cstddef> 
#include <cstdint> 

class SocketArgs {
public:
    SocketArgs(); 
    SocketArgs(size_t bufferSize);
    ~SocketArgs();
    void SetBuffer(const uint8_t* buffer, size_t size);
    bool IsInUse = false;

private:
    size_t bufferSize = 0;
    uint8_t* buffer = nullptr;
};

#endif 
