#include <iostream>
#include "SM2.h"

int main() {
    // Создаем объект SM2
    SM2 sm2;

    // Генерируем ключевую пару
    if (!sm2.generateKeyPair()) {
        std::cerr << "Failed to generate key pair." << std::endl;
        return 1;
    }

    // Пример сообщения для подписи и верификации
    const unsigned char message[] = "Hello, SM2!";
    size_t messageLen = strlen((const char*)message);

    // Выделяем память под подпись (пример, обычно подпись имеет фиксированный размер)
    unsigned char signature[EVP_MAX_MD_SIZE];
    size_t signatureLen;

    // Подписываем сообщение
    if (!sm2.sign(message, messageLen, signature, &signatureLen)) {
        std::cerr << "Failed to sign message." << std::endl;
        return 1;
    }

    std::cout << "Message signed successfully." << std::endl;

    // Выводим подпись в консоль
    std::cout << "Signature: ";
    for (size_t i = 0; i < signatureLen; ++i) {
        printf("%02x", signature[i]);
    }
    std::cout << std::endl;

    return 0;
}