// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <string>
#include <vector>
#include <functional>

class Utils{
    private:
        // Key and IV initialization
        // This function initializes the key and IV for the AES encryption
        // Key length AES key length is 32 bytes
        // IV length AES IV length is 16 bytes
        static const int BLOCKSIZE = CryptoPP::AES::BLOCKSIZE;
        static const int KEY_LENGTH = CryptoPP::AES::DEFAULT_KEYLENGTH;
        Utils() = delete; // Stops instantiation of Utils

    public:
    // Generates the Key and IV
        void initializeKeyAndIV(CryptoPP::byte* key, CryptoPP::byte* iv);

    // Reads entire file into memory
       static std::vector<unsigned char> readFile(const std::string& filePath);

    // Writes data to file
       static void writeFile(const std::vector<unsigned char>& data,
                            const std::string& filePath);

    // Reads file in chunks
       static void readFileInChunks(const std::string& filePath, const std::function<void(const std::vector<unsigned char>&)>& callback,
           size_t chunkSize = 1024 * 1024);

    // Writes file in chunks
       static void writeFileInChunks(const std::string& filePath, const std::vector<unsigned char>& data, size_t chunkSize = 1024 * 1024);

    // Utility file functions
       static bool fileExists(const std::string& filePath);
       static size_t getFileSize(const std::string& filePath);
       static void createDirectories(const std::string& filePath);
};

#endif
