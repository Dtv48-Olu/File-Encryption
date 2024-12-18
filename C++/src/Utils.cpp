// utils.cpp
#include "include/Utils.h"
#include <fstream>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

static void initializeKeyAndIV(CryptoPP::byte* key, CryptoPP::byte* iv) {
    // Generate a random key and IV
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    // Generate a random IV
    rng.GenerateBlock(iv, CryptoPP::AES::BLOCKSIZE);
}

std::vector<unsigned char> Utils::readFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filePath);
    }

    // Get file size
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read file content
    std::vector<unsigned char> buffer(fileSize);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

    if (!file) {
        throw std::runtime_error("Error reading file: " + filePath);
    }

    return buffer;
}

void Utils::writeFile(const std::vector<unsigned char>& data,
                         const std::string& filePath) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot create file: " + filePath);
    }

    file.write(reinterpret_cast<const char*>(data.data()), data.size());

    if (!file) {
        throw std::runtime_error("Error writing file: " + filePath);
    }
}

void Utils::readFileInChunks(
    const std::string& filePath,
    const std::function<void(const std::vector<unsigned char>&)>& callback,
    size_t chunkSize) {

    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filePath);
    }

    std::vector<unsigned char> buffer(chunkSize);
    while (file) {
        file.read(reinterpret_cast<char*>(buffer.data()), chunkSize);
        std::streamsize bytesRead = file.gcount();
        if (bytesRead > 0) {
            buffer.resize(bytesRead);
            callback(buffer);
            buffer.resize(chunkSize);
        }
    }
}

void Utils::writeFileInChunks(
    const std::string& filePath,
    const std::vector<unsigned char>& data,
    size_t chunkSize) {

    std::ofstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot create file: " + filePath);
    }

    size_t totalSize = data.size();
    size_t written = 0;

    while (written < totalSize) {
        size_t currentChunkSize = std::min(chunkSize, totalSize - written);
        file.write(reinterpret_cast<const char*>(data.data() + written),
                  currentChunkSize);
        if (!file) {
            throw std::runtime_error("Error writing file: " + filePath);
        }
        written += currentChunkSize;
    }
}

bool Utils::fileExists(const std::string& filePath) {
    return fs::exists(filePath);
}

size_t Utils::getFileSize(const std::string& filePath) {
    return fs::file_size(filePath);
}

void Utils::createDirectories(const std::string& filePath) {
    fs::path path(filePath);
    fs::create_directories(path.parent_path());
}
