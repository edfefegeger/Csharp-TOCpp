#include "Encryption.h"
#include <string.h>
#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/err.h>

Encryption::Encryption() {
    printf("[Encryption] Initializing key...\n");
    InitializeKey();
    printf("[Encryption] Key initialization complete.\n");
}

Encryption::~Encryption() {
    printf("[Encryption] Clearing key...\n");
    ClearKey();
    printf("[Encryption] Key cleared.\n");
}

void Encryption::InitializeKey() {
    const char* defaultKey = "default_key_1234";  
    printf("[Encryption] Initializing key with: %s\n", defaultKey);


    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        Key[i] = defaultKey[i];
    }

    printf("[Encryption] Key initialized.\n");
}

void Encryption::ClearKey() {
    printf("[Encryption] Clearing key values...\n");

    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        Key[i] = 0;
    }
    printf("[Encryption] Key values cleared.\n");
}

void Encryption::EncryptBytes(const unsigned char* input, unsigned int inputLen, unsigned char* output, unsigned int& outputLen) {
    printf("[Encryption] Starting encryption...\n");

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL) {
        printf("[Encryption] Failed to create EVP context.\n");
        return;
    }


    printf("[Encryption] Initializing encryption...\n");
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, Key, NULL)) {
        printf("[Encryption] Encryption initialization failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    printf("[Encryption] Encryption initialized successfully.\n");

    int len;
    outputLen = 0;
    printf("[Encryption] Encrypting data...\n");
    if (1 != EVP_EncryptUpdate(ctx, output, &len, input, inputLen)) {
        printf("[Encryption] Encryption update failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    outputLen += len;
    printf("[Encryption] Encryption update complete. Bytes encrypted: %d\n", len);


    printf("[Encryption] Finalizing encryption...\n");
    if (1 != EVP_EncryptFinal_ex(ctx, output + outputLen, &len)) {
        printf("[Encryption] Encryption finalization failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    outputLen += len;
    printf("[Encryption] Encryption finalization complete. Total encrypted bytes: %d\n", outputLen);

    EVP_CIPHER_CTX_free(ctx);
    printf("[Encryption] Encryption complete.\n");
}

void Encryption::DecryptBytes(const unsigned char* input, unsigned int inputLen, unsigned char* output, unsigned int& outputLen) {
    printf("[Encryption] Starting decryption...\n");

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL) {
        printf("[Encryption] Failed to create EVP context.\n");
        return;
    }


    printf("[Encryption] Initializing decryption...\n");
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, Key, NULL)) {
        unsigned long err = ERR_get_error();
        printf("[Encryption] Decryption initialization failed. OpenSSL Error code: %lu\n", err);
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    printf("[Encryption] Decryption initialized successfully.\n");

    int len;
    outputLen = 0;


    printf("[Encryption] Decrypting data...\n");
    if (1 != EVP_DecryptUpdate(ctx, output, &len, input, inputLen)) {
        unsigned long err = ERR_get_error();
        printf("[Encryption] Decryption update failed. OpenSSL Error code: %lu\n", err);
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    outputLen += len;
    printf("[Encryption] Decryption update complete. Bytes decrypted: %d\n", len);


    printf("[Encryption] Finalizing decryption...\n");
    if (1 != EVP_DecryptFinal_ex(ctx, output + outputLen, &len)) {
        unsigned long err = ERR_get_error();
        
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    outputLen += len;
    printf("[Encryption] Decryption finalization complete. Total decrypted bytes: %d\n", outputLen);

    EVP_CIPHER_CTX_free(ctx);
    printf("[Encryption] Decryption complete.\n");
}
