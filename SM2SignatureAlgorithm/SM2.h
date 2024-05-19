// sm2_crypto.h
#ifndef SM2_CRYPTO_H
#define SM2_CRYPTO_H

#include <openssl/evp.h>

class SM2 {
public:
    SM2();
    ~SM2();

    bool generateKeyPair();

    bool sign(const unsigned char* message, size_t messageLen, unsigned char* signature, size_t* signatureLen);

    bool verify(const unsigned char* message, size_t messageLen, const unsigned char* signature, size_t signatureLen);

private:
    EVP_PKEY* pkey_;
};

#endif // SM2_CRYPTO_H
