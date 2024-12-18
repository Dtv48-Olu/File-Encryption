#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "Cryptography.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <string>
#include <vector>

class Encryption : public Crytography {
    private:
        // Add these member variables
        CryptoPP::SecByteBlock key;
        std::vector<unsigned char> iv;
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryptor;

        void generateKey();
        void applyCipher(std::vector<unsigned char>& data) override;
        void padData(std::vector<unsigned char>& data);
        void randomizeInitializationVector();
        void initCipherMode();

    public:
        Encryption();
        ~Encryption();
        void processFile(const std::string& inputFile, const std::string& outputFile) override;
};

#endif
