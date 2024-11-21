#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#define AES_BLOCK_SIZE 16

#include <openssl/aes.h>

class Encryption {
public:
    Encryption();
    ~Encryption();

    void EncryptBytes(const unsigned char* input, unsigned int inputLen, unsigned char* output, unsigned int& outputLen);
    void DecryptBytes(const unsigned char* input, unsigned int inputLen, unsigned char* output, unsigned int& outputLen);

private:
    unsigned char Key[AES_BLOCK_SIZE]; 

    AES_KEY encryptKey;        
    AES_KEY decryptKey;              

    void InitializeKey();
    void ClearKey();        
    void AES_EncryptBlock(const unsigned char* input, unsigned char* output);
    void AES_DecryptBlock(const unsigned char* input, unsigned char* output);
};

#endif 
