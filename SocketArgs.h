#ifndef SOCKETARGS_H
#define SOCKETARGS_H

#include <cstddef> // Для size_t
#include <cstdint> // Для uint8_t

class SocketArgs {
public:
    SocketArgs(); // Конструктор по умолчанию
    SocketArgs(size_t bufferSize);
    ~SocketArgs();
    void SetBuffer(const uint8_t* buffer, size_t size);
    bool IsInUse = false;

private:
    size_t bufferSize = 0;
    uint8_t* buffer = nullptr; // Инициализация указателя
};

#endif // SOCKETARGS_HPP
