#include "include/Decryption.h"
#include "include/Utils.h"
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>

using namespace CryptoPP;

Decryption::Decryption() {
    // Initialize any necessary components
    key.resize(AES::DEFAULT_KEYLENGTH);
    iv.resize(AES::BLOCKSIZE);
}

Decryption::~Decryption() {
    // Clean up any sensitive data
}

void Decryption::setKey(const byte* keyData, size_t keySize) {
    if (keySize != AES::DEFAULT_KEYLENGTH) {
        throw std::runtime_error("Invalid key size");
    }
    key.Assign(keyData, keySize);
}

void Decryption::setIV(const byte* ivData, size_t ivSize) {
    if (ivSize != AES::BLOCKSIZE) {
        throw std::runtime_error("Invalid IV size");
    }
    iv.assign(ivData, ivData + ivSize);
}

void Decryption::initDecryptor() {
    decryptor.SetKeyWithIV(key.data(), key.size(), iv.data(), iv.size());
}

void Decryption::extractIV(std::vector<unsigned char>& data) {
    if (data.size() < AES::BLOCKSIZE) {
        throw std::runtime_error("Input data too small to contain IV");
    }

    // Extract IV from the beginning of the data
    iv.assign(data.begin(), data.begin() + AES::BLOCKSIZE);

    // Remove IV from the data
    data.erase(data.begin(), data.begin() + AES::BLOCKSIZE);
}

void Decryption::applyCipher(std::vector<unsigned char>& data) {
    try {
        std::vector<unsigned char> decrypted;
        decrypted.resize(data.size());

        // Perform decryption
        decryptor.ProcessData(
            decrypted.data(),
            data.data(),
            data.size()
        );

        // Replace input data with decrypted data
        data = std::move(decrypted);

    } catch (const CryptoPP::Exception& e) {
        throw std::runtime_error("Decryption failed: " + std::string(e.what()));
    }
}

void Decryption::removePadding(std::vector<unsigned char>& data) {
    if (data.empty()) {
        throw std::runtime_error("No data to remove padding from");
    }

    // Get the padding length from the last byte
    unsigned char paddingLength = data.back();

    if (paddingLength > AES::BLOCKSIZE || paddingLength > data.size()) {
        throw std::runtime_error("Invalid padding");
    }

    // Remove padding bytes
    data.resize(data.size() - paddingLength);
}

void Decryption::processFile(const std::string& inputFile, const std::string& outputFile) {
    try {
        // Read encrypted file
        auto data = Utils::readFile(inputFile);

        // Extract IV from the beginning of the file
        extractIV(data);

        // Initialize decryptor with key and extracted IV
        initDecryptor();

        // Decrypt the data
        applyCipher(data);

        // Remove padding
        removePadding(data);

        // Write decrypted data to output file
        Utils::writeFile(data, outputFile);

    } catch (const std::exception& e) {
        throw std::runtime_error("File processing failed: " + std::string(e.what()));
    }
}
