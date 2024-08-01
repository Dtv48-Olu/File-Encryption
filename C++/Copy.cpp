#include "Copy.h"
#include <iostream>
#include <fstream>

void Copy::doFilter(std::ifstream& in, std::ofstream& out) {
    if (!in.is_open()) {
        std::cerr << "Error: File cannot be opened" << std::endl;
        return; // Early exit to avoid further issues
    }

    char letter;
    // Read and write character by character
    while (in.get(letter)) {
        out.put(letter); // Output the copied character
    }
}
