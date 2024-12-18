#include "include/Encryption.h"
#include "include/Utils.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <cryptopp/secblock.h>
#include <stdexcept>

using namespace CryptoPP;

 Encryption::Encryption() {
    generateKey();
    randomizeInitializationVector();
    initCipherMode();
 }

Encryption::~Encryption() {
    key.resize(0);  // SecByteBlock has secure cleanup
    std::fill(iv.begin(), iv.end(), 0);  // Zero out IV
    iv.clear();
}

void Encryption::generateKey() {
    // Use CryptoPP's secure random number generator
    AutoSeededRandomPool prng;

    // Generate a random key (for AES-256)
    key.resize(AES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock(key.data(), key.size());
}

void Encryption::randomizeInitializationVector() {
    // Generate random IV
    AutoSeededRandomPool prng;

    iv.resize(AES::BLOCKSIZE);
    prng.GenerateBlock(iv.data(), iv.size());
}

void Encryption::initCipherMode() {
    // Initialize encryption objects with key and IV
    // This depends on your chosen cipher mode (CBC, GCM, etc.)
    encryptor.SetKeyWithIV(key.data(), key.size(), iv.data(), iv.size());
}

void Encryption::padData(std::vector<unsigned char>& data) {
    // Implement PKCS7 padding
    size_t blockSize = AES::BLOCKSIZE;
    size_t paddingLength = blockSize - (data.size() % blockSize);

    // Add padding bytes
    for (size_t i = 0; i < paddingLength; i++) {
        data.push_back(static_cast<unsigned char>(paddingLength));
    }
}

void Encryption::applyCipher(std::vector<unsigned char>& data) {
    try {
        std::vector<unsigned char> encrypted;
        encrypted.resize(data.size());

        // Perform encryption
        encryptor.ProcessData(
            encrypted.data(),
            data.data(),
            data.size()
        );

        // Replace input data with encrypted data
        data = std::move(encrypted);

    } catch (const CryptoPP::Exception& e) {
        throw std::runtime_error("Encryption failed: " + std::string(e.what()));
    }
}

void Encryption::processFile(const std::string& inputFile, const std::string& outputFile) {
    try {
        // Read input file
        auto data = Utils::readFile(inputFile);

        // Add padding if necessary
        padData(data);

        // Encrypt the data
        applyCipher(data);

        // Prepend IV to encrypted data
        std::vector<unsigned char> finalData;
        finalData.insert(finalData.end(), iv.begin(), iv.end());
        finalData.insert(finalData.end(), data.begin(), data.end());

        // Write the result to output
        Utils::writeFile(finalData, outputFile);

    } catch (const std::exception& e) {
        throw std::runtime_error("File processing failed: " + std::string(e.what()));
    }
}
