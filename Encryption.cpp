#include "Encryption.h"
#include <cstring>
#include <iostream>
#include <random>

Encryption::Encryption() {
    InitializeKey();
}

Encryption::~Encryption() {
    // ������� �����
    std::memset(Key, 0, AES_BLOCK_SIZE);
}

void Encryption::InitializeKey() {
    // ������ ��������� �����
    const char* defaultKey = "default_key_1234";  // ����������� ��� ���� ��� ������ ��� ���������
    std::memcpy(Key, defaultKey, AES_BLOCK_SIZE);
}

void Encryption::AES_EncryptBlock(const unsigned char* input, unsigned char* output) {
    // ������� ������ ���������� � ������ ECB (��� ������������� ������� ���������)
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        output[i] = input[i] ^ Key[i % AES_BLOCK_SIZE]; // ������ ������� �������� XOR
    }
}

void Encryption::AES_DecryptBlock(const unsigned char* input, unsigned char* output) {
    // ������� ������ ������������ � ������ ECB
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        output[i] = input[i] ^ Key[i % AES_BLOCK_SIZE]; // ������ ������������� ������������ � �������������� XOR
    }
}

void Encryption::EncryptBytes(const unsigned char* input, unsigned int inputLen, unsigned char* output, unsigned int& outputLen) {
    unsigned char iv[AES_BLOCK_SIZE] = { 0 };  // IV ����� ������������ ��������� �������
    unsigned int blockCount = (inputLen / AES_BLOCK_SIZE) + (inputLen % AES_BLOCK_SIZE == 0 ? 0 : 1);

    unsigned int outputIndex = 0;
    for (unsigned int i = 0; i < blockCount; ++i) {
        // ��������� ��������� ������, ���� �����
        unsigned int blockSize = (i == blockCount - 1 && inputLen % AES_BLOCK_SIZE != 0) ? inputLen % AES_BLOCK_SIZE : AES_BLOCK_SIZE;
        unsigned char block[AES_BLOCK_SIZE] = { 0 };
        std::memcpy(block, input + i * AES_BLOCK_SIZE, blockSize);

        AES_EncryptBlock(block, output + outputIndex);  // ������� ����
        outputIndex += AES_BLOCK_SIZE;
    }

    outputLen = outputIndex;
}

void Encryption::DecryptBytes(const unsigned char* input, unsigned int inputLen, unsigned char* output, unsigned int& outputLen) {
    unsigned int blockCount = inputLen / AES_BLOCK_SIZE;

    unsigned int outputIndex = 0;
    for (unsigned int i = 0; i < blockCount; ++i) {
        AES_DecryptBlock(input + i * AES_BLOCK_SIZE, output + outputIndex);  // ��������� ����
        outputIndex += AES_BLOCK_SIZE;
    }

    outputLen = outputIndex;
}
