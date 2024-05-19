#include <iostream>
#include "SM2.h"

int main() {
    SM2 sm2;

    if (!sm2.generateKeyPair()) {
        std::cerr << "Failed to generate key pair." << std::endl;
        return 1;
    }

    const unsigned char message[] = "Hello, SM2!";
    size_t messageLen = strlen((const char*)message);

    unsigned char signature[EVP_MAX_MD_SIZE];
    size_t signatureLen;

    if (!sm2.sign(message, messageLen, signature, &signatureLen)) {
        std::cerr << "Failed to sign message." << std::endl;
        return 1;
    }

    std::cout << "Message signed successfully." << std::endl;

    std::cout << "Signature: ";
    for (size_t i = 0; i < signatureLen; ++i) {
        printf("%02x", signature[i]);
    }
    std::cout << std::endl;
    
    bool verify = sm2.verify(message, messageLen, signature, signatureLen);
    if (verify) {
        std::cout << "Signature has been verified successfully!\n ";
    }
    else {
        std::cout << "Signature has not been verified! Something went wrong!\n";
    }

    return 0;
}

