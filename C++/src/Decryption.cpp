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
    key.resize(0);  // SecByteBlock has secure cleanup
    std::fill(iv.begin(), iv.end(), 0);  // Zero out IV
    iv.clear();
}

void Decryption::setKey(const byte* keyData, size_t keySize) {
    if (keySize != AES::DEFAULT_KEYLENGTH) {
        throw std::runtime_error("Invalid key size");
    }
    key.Assign(keyData, keySize);

    // Print key for debugging
    std::cout << "Key set: ";
    for (size_t i = 0; i < key.size(); i++) {
        printf("%02X ", key[i]);
    }
    std::cout << std::endl;
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

    unsigned char paddingLength = data.back();
    std::cout << "Padding length byte: " << (int)paddingLength << std::endl;

    if (paddingLength == 0 || paddingLength > AES::BLOCKSIZE) {
        std::cout << "Warning: Unusual padding length: " << (int)paddingLength << std::endl;
        // For debugging, don't throw error yet
    }

    if (paddingLength > data.size()) {
        throw std::runtime_error("Padding length larger than data size");
    }

    // Check padding bytes
    bool paddingValid = true;
    for (size_t i = 0; i < paddingLength && i < data.size(); i++) {
        if (data[data.size() - 1 - i] != paddingLength) {
            std::cout << "Invalid padding at position -" << i+1 << ": expected "
                      << (int)paddingLength << ", got " << (int)data[data.size() - 1 - i] << std::endl;
            paddingValid = false;
            break;
        }
    }

    if (!paddingValid) {
        std::cout << "Padding validation failed, but continuing for debugging\n";
        // Instead of throwing an error, just remove the last byte for debugging
        data.pop_back();
    } else {
        // Remove padding if it seems valid
        data.resize(data.size() - paddingLength);
    }
}

void Decryption::processFile(const std::string& inputFile, const std::string& outputFile) {
    try {
        // Read encrypted file
        auto data = Utils::readFile(inputFile);
        std::cout << "File read successfully. Size: " << data.size() << " bytes\n";

        // Extract IV from the beginning of the file
        std::cout << "Extracting IV...\n";
        extractIV(data);
        std::cout << "IV extracted. Data size after IV removal: " << data.size() << " bytes\n";

        // Print IV for debugging
        std::cout << "IV: ";
        for (byte b : iv) {
            printf("%02X ", b);
        }
        std::cout << std::endl;

        // Initialize decryptor with key and extracted IV
        std::cout << "Initializing decryptor...\n";
        initDecryptor();

        // Decrypt the data
        std::cout << "Decrypting data...\n";
        applyCipher(data);
        std::cout << "Data decrypted. Size: " << data.size() << " bytes\n";

        // Remove padding
        std::cout << "Removing padding...\n";
        // Print last few bytes to check padding
        std::cout << "Last byte (padding length): " << (int)data.back() << std::endl;
        removePadding(data);
        std::cout << "Padding removed. Final size: " << data.size() << " bytes\n";

        // Write decrypted data to output file
        std::cout << "Writing to output file...\n";
        Utils::writeFile(data, outputFile);
        std::cout << "File written successfully\n";

    } catch (const std::exception& e) {
        throw std::runtime_error("File processing failed: " + std::string(e.what()));
    }
}
