#include "SocketArgs.h"

SocketArgs::SocketArgs(size_t bufferSize)
    : bufferSize(bufferSize), buffer(bufferSize) { }

void SocketArgs::SetBuffer(const std::vector<uint8_t>& buffer) {
    if (buffer.size() <= bufferSize) {
        this->buffer = buffer; // Устанавливаем буфер
    }
}
