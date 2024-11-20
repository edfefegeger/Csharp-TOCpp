#include "Encryption.h"
#include <cstring>
#include <iostream>
#include <random>

Encryption::Encryption() {
    InitializeKey();
}

Encryption::~Encryption() {
    // Очистка ключа
    std::memset(Key, 0, AES_BLOCK_SIZE);
}

void Encryption::InitializeKey() {
    // Пример генерации ключа
    const char* defaultKey = "default_key_1234";  // Используйте ваш ключ или способ его получения
    std::memcpy(Key, defaultKey, AES_BLOCK_SIZE);
}

void Encryption::AES_EncryptBlock(const unsigned char* input, unsigned char* output) {
    // Простой пример шифрования в режиме ECB (без использования внешних библиотек)
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        output[i] = input[i] ^ Key[i % AES_BLOCK_SIZE]; // Пример простой операции XOR
    }
}

void Encryption::AES_DecryptBlock(const unsigned char* input, unsigned char* output) {
    // Простой пример дешифрования в режиме ECB
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        output[i] = input[i] ^ Key[i % AES_BLOCK_SIZE]; // Пример симметричного дешифрования с использованием XOR
    }
}

void Encryption::EncryptBytes(const unsigned char* input, unsigned int inputLen, unsigned char* output, unsigned int& outputLen) {
    unsigned char iv[AES_BLOCK_SIZE] = { 0 };  // IV можно использовать случайным образом
    unsigned int blockCount = (inputLen / AES_BLOCK_SIZE) + (inputLen % AES_BLOCK_SIZE == 0 ? 0 : 1);

    unsigned int outputIndex = 0;
    for (unsigned int i = 0; i < blockCount; ++i) {
        // Дополняем последние данные, если нужно
        unsigned int blockSize = (i == blockCount - 1 && inputLen % AES_BLOCK_SIZE != 0) ? inputLen % AES_BLOCK_SIZE : AES_BLOCK_SIZE;
        unsigned char block[AES_BLOCK_SIZE] = { 0 };
        std::memcpy(block, input + i * AES_BLOCK_SIZE, blockSize);

        AES_EncryptBlock(block, output + outputIndex);  // Шифруем блок
        outputIndex += AES_BLOCK_SIZE;
    }

    outputLen = outputIndex;
}

void Encryption::DecryptBytes(const unsigned char* input, unsigned int inputLen, unsigned char* output, unsigned int& outputLen) {
    unsigned int blockCount = inputLen / AES_BLOCK_SIZE;

    unsigned int outputIndex = 0;
    for (unsigned int i = 0; i < blockCount; ++i) {
        AES_DecryptBlock(input + i * AES_BLOCK_SIZE, output + outputIndex);  // Дешифруем блок
        outputIndex += AES_BLOCK_SIZE;
    }

    outputLen = outputIndex;
}
