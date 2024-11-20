#ifndef SOCKETARGS_HPP
#define SOCKETARGS_HPP

#include <vector>
#include <cstdint> // для uint8_t

class SocketArgs {
public:
    SocketArgs(size_t bufferSize);
    void SetBuffer(const std::vector<uint8_t>& buffer);
    bool IsInUse = false;

private:
    size_t bufferSize;
    std::vector<uint8_t> buffer; // Буфер данных
};

#endif // SOCKETARGS_HPP
