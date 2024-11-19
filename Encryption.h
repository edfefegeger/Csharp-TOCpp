#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#define AES_BLOCK_SIZE 16

class Encryption {
public:
    Encryption();
    ~Encryption();

    void EncryptBytes(const unsigned char* input, unsigned int inputLen, unsigned char* output, unsigned int& outputLen);
    void DecryptBytes(const unsigned char* input, unsigned int inputLen, unsigned char* output, unsigned int& outputLen);

private:
    unsigned char Key[AES_BLOCK_SIZE];

    void InitializeKey();
};

#endif // ENCRYPTION_H
