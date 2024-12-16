// encryption.h
#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <string>

std::string encrypt(const std::string& plaintext, const CryptoPP::byte* key, const CryptoPP::byte* iv);

#endif
