#include "Encryption.h"
#include <string.h>
#include <iostream>
#include <openssl/evp.h>

Encryption::Encryption() {
    InitializeKey();
}

Encryption::~Encryption() {
    ClearKey();
}

void Encryption::InitializeKey() {
    // Пример генерации ключа
    const char* defaultKey = "default_key_1234";  // Используйте ваш ключ или способ его получения
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        Key[i] = defaultKey[i];
    }
}

void Encryption::ClearKey() {
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        Key[i] = 0;
    }
}

void Encryption::EncryptBytes(const unsigned char* input, unsigned int inputLen, unsigned char* output, unsigned int& outputLen) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL) {
        // Вывод ошибки с использованием стандартных функций C
        printf("Failed to create EVP context.\n");
        return;
    }

    // Инициализация шифрования
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, Key, NULL)) {
        printf("Encryption initialization failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }

    int len;
    outputLen = 0;
    if (1 != EVP_EncryptUpdate(ctx, output, &len, input, inputLen)) {
        printf("Encryption update failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    outputLen += len;

    if (1 != EVP_EncryptFinal_ex(ctx, output + outputLen, &len)) {
        printf("Encryption finalization failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    outputLen += len;

    EVP_CIPHER_CTX_free(ctx);
}

void Encryption::DecryptBytes(const unsigned char* input, unsigned int inputLen, unsigned char* output, unsigned int& outputLen) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL) {
        printf("Failed to create EVP context.\n");
        return;
    }

    // Инициализация дешифрования
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, Key, NULL)) {
        printf("Decryption initialization failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }

    int len;
    outputLen = 0;
    if (1 != EVP_DecryptUpdate(ctx, output, &len, input, inputLen)) {
        printf("Decryption update failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    outputLen += len;

    if (1 != EVP_DecryptFinal_ex(ctx, output + outputLen, &len)) {
        printf("Decryption finalization failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    outputLen += len;

    EVP_CIPHER_CTX_free(ctx);
}
