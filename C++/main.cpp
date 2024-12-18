// Olutoye O
// odufowokantoye@outlook
// Date Started: 7-13-24
// Description: The following project purpose is demostrate a simpilistic version of file encryption and proper c++ security pratices

#include <iostream>
#include "src/include/Encryption.h"
#include "src/include/Decryption.h"

void displayMenu() {
    std::cout << "\nFile Encryption/Decryption Program\n"
              << "==================================\n"
              << "1. Encrypt a file\n"
              << "2. Decrypt a file\n"
              << "3. Exit\n"
              << "Enter your choice (1-3): ";
}

void processEncryption() {
    std::string inputFile, outputFile;

    std::cout << "Enter the name of the file to encrypt: ";
    std::getline(std::cin, inputFile);

    std::cout << "Enter the name for the encrypted file: ";
    std::getline(std::cin, outputFile);

    try {
        Encryption encryptor;
        encryptor.processFile(inputFile, outputFile);
        std::cout << "File encrypted successfully!\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Encryption failed: " << e.what() << std::endl;
    }
}

void processDecryption() {
    std::string inputFile, outputFile;

    std::cout << "Enter the name of the file to decrypt: ";
    std::getline(std::cin, inputFile);

    std::cout << "Enter the name for the decrypted file: ";
    std::getline(std::cin, outputFile);

    try {
        Decryption decryptor;
        decryptor.processFile(inputFile, outputFile);
        std::cout << "File decrypted successfully!\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Decryption failed: " << e.what() << std::endl;
    }
}

int main() {
    std::string choice;

    while (true) {
        displayMenu();
        std::getline(std::cin, choice);

        if (choice == "1") {
            processEncryption();
        }
        else if (choice == "2") {
            processDecryption();
        }
        else if (choice == "3") {
            std::cout << "Thank you for using the program!\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
