#ifndef SOCKETARGS_HPP
#define SOCKETARGS_HPP

#include <vector>
#include <string>

class SocketArgs {
public:
    SocketArgs(size_t bufferSize);
    void SetBuffer(const std::vector<uint8_t>& buffer);
    bool IsInUse = false;


private:
    size_t bufferSize;
};

#endif
