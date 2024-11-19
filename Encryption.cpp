#include "Encryption.h"
#include <cstring>

Encryption::Encryption() {
    InitializeKey();
}

Encryption::~Encryption() {
    // Очистка ключа
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        Key[i] = 0;
    }
}

void Encryption::InitializeKey() {
    // Пример генерации ключа
    const char* defaultKey = "default_key_1234";
    memcpy(Key, defaultKey, AES_BLOCK_SIZE);
}

void Encryption::EncryptBytes(const unsigned char* input, unsigned int inputLen, unsigned char* output, unsigned int& outputLen) {
    // Пример шифрования XOR (замените на реальный алгоритм)
    for (unsigned int i = 0; i < inputLen; ++i) {
        output[i] = input[i] ^ Key[i % AES_BLOCK_SIZE];
    }
    outputLen = inputLen;
}

void Encryption::DecryptBytes(const unsigned char* input, unsigned int inputLen, unsigned char* output, unsigned int& outputLen) {
    // Пример дешифрования XOR (симметричное)
    for (unsigned int i = 0; i < inputLen; ++i) {
        output[i] = input[i] ^ Key[i % AES_BLOCK_SIZE];
    }
    outputLen = inputLen;
}
