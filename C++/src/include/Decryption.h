#ifndef DECRYPTION_H  // Changed from ENCRYPTION_H to DECRYPTION_H
#define DECRYPTION_H

#include "Cryptography.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <string>
#include <vector>
#include <stdexcept>

class Decryption : public Crytography {
private:
    CryptoPP::SecByteBlock key;
    std::vector<unsigned char> iv;
    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryptor;

    void initDecryptor();
    void applyCipher(std::vector<unsigned char>& data) override;
    void removePadding(std::vector<unsigned char>& data);
    void extractIV(std::vector<unsigned char>& data);

public:
    Decryption();
    ~Decryption();

    void processFile(const std::string& inputFile, const std::string& outputFile) override;
    void setKey(const CryptoPP::byte* keyData, size_t keySize);
    void setIV(const CryptoPP::byte* ivData, size_t ivSize);
};

#endif
