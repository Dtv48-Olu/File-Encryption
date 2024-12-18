#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "Utils.h"
#include "Cryptography.h" // adding base class
#include <string>

class Encryption : public Crytography {
    private:
        void generateKey();
        void applyCipher(std::vector<unsigned char>& data) override;
        void padData(std::vector<unsigned char>& data);
        void randomizeInitializationVector();
        void initCipherMode();


    public:
        // Constructor
        Encryption();
        // Destructor
        // ~Encryption();

        // Overiding the virtual function
        void processFile(const std::string& inputFile, const std::string& outputFile) override;
};

#endif
