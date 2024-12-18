#include "include/Encryption.h"
#include <cryptopp/seckey.h>

Encryption::Encryption() {
    // Constructor implementation
}

void processFile(const std::string& inputFile, const std::string& outputFile) override {
    auto data = Utils::readFile(inputFile);
    padData(data);                        // Add padding if necessary
    applyCipher(data);                    // Encrypt the data
    Utils::writeFile(outputFile, data);   // Write the result to output
}

void generateKey() {
    intal
}
