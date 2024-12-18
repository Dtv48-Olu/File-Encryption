#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

// The abstract base class using OOP programming principles
#include <cryptopp/config_int.h>
#include <cryptopp/aes.h>
#include <string>
#include <vector>
class Crytography {
    protected:
        // Variables
        CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];
        CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
    public:
        // Pure virtual functions
        virtual void processFile(const std::string& inputFile, const std::string& outputFile) = 0;
        virtual void applyCipher(std::vector<unsigned char>& data) = 0;
};

#endif
