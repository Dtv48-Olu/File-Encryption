#include "Encryption.h"
#include <iostream>
#include <fstream>

Encryption::Encryption(int Key_value) {
    Key = Key_value; // Overloaded constructor
}

Encryption::Encryption() {
    Key = 5; // Default constructor with a key of 5
}

void Encryption::doFilter(std::ifstream& in, std::ofstream& out) {
    // Ensure the file is open
    if (!in.is_open()) {
        std::cerr << "Error: File cannot be opened" << std::endl;
        return;
    }

    char letter;

    // Reading character by character
    while (in.get(letter)) {
        // Get ASCII value
        int ASCII = static_cast<int>(letter);
        int Encryption_ASCII = ASCII + Key;

        // Wrap around logic
        if (Encryption_ASCII < 32) {
            Encryption_ASCII = 126 - (32 - Encryption_ASCII - 1);
        } else if (Encryption_ASCII > 126) {
            Encryption_ASCII = 32 + (Encryption_ASCII - 126 - 1);
        }

        out.put(static_cast<char>(Encryption_ASCII)); // Outputting the encrypted character
    }
}
