#ifndef SOCKETARGS_HPP
#define SOCKETARGS_HPP

#include <vector>
#include <string>

class SocketArgs {
public:
    SocketArgs(size_t bufferSize);
    void SetBuffer(const std::vector<uint8_t>& buffer);

    std::vector<uint8_t> Buffer;
    bool IsInUse = false;
    std::string RecipientID;

private:
    size_t bufferSize;
};

#endif
