#include "SM2.h"
#include <openssl/ec.h>
#include <openssl/objects.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <iostream>

SM2::SM2() : pkey_(nullptr) {}

SM2::~SM2() {
    if (pkey_) {
        EVP_PKEY_free(pkey_);
    }
}

bool SM2::generateKeyPair() {
    EC_KEY* ec_key = EC_KEY_new();
    if (!ec_key) {
        std::cerr << "Failed to create EC_KEY." << std::endl;
        return false;
    }

    int nid = NID_sm2;

    EC_GROUP* ec_group = EC_GROUP_new_by_curve_name(nid);
    if (!ec_group) {
        std::cerr << "Failed to create EC_GROUP." << std::endl;
        EC_KEY_free(ec_key);
        return false;
    }


    if (EC_KEY_set_group(ec_key, ec_group) != 1) {
        EC_GROUP_free(ec_group);
        EC_KEY_free(ec_key);
        return false;
    }

    if (EC_KEY_generate_key(ec_key) != 1) {
        EC_GROUP_free(ec_group);
        EC_KEY_free(ec_key);
        return false;
    }

    pkey_ = EVP_PKEY_new();
    if (!pkey_) {
        EC_GROUP_free(ec_group);
        EC_KEY_free(ec_key);
        return false;
    }

    if (EVP_PKEY_assign_EC_KEY(pkey_, ec_key) != 1) {
        EVP_PKEY_free(pkey_);
        EC_GROUP_free(ec_group);
        EC_KEY_free(ec_key);
        return false;
    }

    EC_GROUP_free(ec_group);
    return true;
}

bool SM2::sign(const unsigned char* message, size_t messageLen, unsigned char* signature, size_t* signatureLen) {
    if (!pkey_) {
        return false;
    }

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) {
        return false;
    }

    const EVP_MD* md = EVP_sm3(); // Создаем объект EVP_MD для хэш-функции SM3

    if (EVP_DigestSignInit(ctx, NULL, md, NULL, pkey_) != 1) {
        EVP_MD_CTX_free(ctx);
        return false;
    }

    if (EVP_DigestSignUpdate(ctx, message, messageLen) != 1) {
        EVP_MD_CTX_free(ctx);
        return false;
    }

    size_t sigLen = *signatureLen; // Сохраняем значение, чтобы не изменять переданное значение

    if (EVP_DigestSignFinal(ctx, NULL, &sigLen) != 1) { // Вызываем с NULL, чтобы получить длину подписи
        EVP_MD_CTX_free(ctx);
        return false;
    }

    if (sigLen > *signatureLen) { // Проверяем, достаточно ли места в буфере подписи
        EVP_MD_CTX_free(ctx);
        return false;
    }

    if (EVP_DigestSignFinal(ctx, signature, &sigLen) != 1) { // Вызываем с правильной длиной буфера подписи
        EVP_MD_CTX_free(ctx);
        return false;
    }

    *signatureLen = sigLen; // Обновляем переданное значение длины подписи
    EVP_MD_CTX_free(ctx);
    return true;
}

bool SM2::verify(const unsigned char* message, size_t messageLen, const unsigned char* signature, size_t signatureLen) {
    if (!pkey_) {
        return false;
    }

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) {
        return false;
    }

    const EVP_MD* md = EVP_sm3(); // Создаем объект EVP_MD для хэш-функции SM3

    if (EVP_DigestVerifyInit(ctx, NULL, md, NULL, pkey_) != 1) {
        EVP_MD_CTX_free(ctx);
        return false;
    }

    if (EVP_DigestVerifyUpdate(ctx, message, messageLen) != 1) {
        EVP_MD_CTX_free(ctx);
        return false;
    }

    int result = EVP_DigestVerifyFinal(ctx, signature, signatureLen);
    EVP_MD_CTX_free(ctx);

    return (result == 1);
}