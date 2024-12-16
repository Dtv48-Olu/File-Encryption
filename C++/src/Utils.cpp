// utils.cpp
#include "include/Utils.h"


// Key and IV initialization
// This function initializes the key and IV for the AES encryption
class Utils {
// Key length AES key length is 32 bytes
// IV length AES IV length is 16 bytes
private:
    static const int BLOCKSIZE = CryptoPP::AES::BLOCKSIZE;
    static const int KEY_LENGTH = CryptoPP::AES::DEFAULT_KEYLENGTH;
public:
    static void initializeKeyAndIV(CryptoPP::byte* key, CryptoPP::byte* iv) {
        // Generate a random key and IV
        CryptoPP::AutoSeededRandomPool rng;
        rng.GenerateBlock(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        // Generate a random IV
        rng.GenerateBlock(iv, CryptoPP::AES::BLOCKSIZE);
    };
}
