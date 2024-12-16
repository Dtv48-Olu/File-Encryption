// decryption.h
#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <string>

std::string decrypt(const std::string& ciphertext, const CryptoPP::byte* key, const CryptoPP::byte* iv);

#endif
