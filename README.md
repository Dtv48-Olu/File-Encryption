# File Encryption Program

A secure file encryption and decryption program implemented in C++ using the Crypto++ library. This program provides a command-line interface for encrypting and decrypting files using AES-256 encryption in CBC mode.

## Features

- File encryption using AES-256 encryption
- CBC (Cipher Block Chaining) mode of operation
- Secure random key and IV generation
- PKCS7 padding
- File handling with chunking support for large files
- Error handling and input validation
- Cross-platform compatibility

## Prerequisites

- C++17 or higher
- CMake 3.10 or higher
- Crypto++ library (libcryptopp)
- A C++ compiler (GCC, Clang, etc.)

## Building the Project

1. Create a build directory:
```bash
mkdir build && cd build
```

2. Generate build files with CMake:
```bash
cmake ..
```

3. Build the project:
```bash
make
```

## Usage

After building, run the program:

```bash
./File-Encryption
```

The program provides a menu-driven interface with the following options:
1. Encrypt a file
2. Decrypt a file
3. Exit

### Encryption
- Enter the source file path when prompted
- Enter the destination path for the encrypted file
- The program will encrypt the file using AES-256 encryption

### Decryption
- Enter the path of the encrypted file
- Enter the destination path for the decrypted file
- The program will decrypt the file

## Project Structure

```
File-Encryption/
├── CMakeLists.txt
├── main.cpp
├── src/
│   ├── Encryption.cpp
│   ├── Decryption.cpp
│   ├── Utils.cpp
│   └── include/
│       ├── Cryptography.h
│       ├── Encryption.h
│       ├── Decryption.h
│       └── Utils.h
├── build/
└── README.md
```

## Technical Details

- Uses AES-256 encryption in CBC mode
- Implements secure random number generation for keys and IVs
- Uses PKCS7 padding for block alignment
- Includes IV with encrypted data for secure decryption
- Implements proper memory cleanup for sensitive data

## Security Features

- Secure key generation using Crypto++'s AutoSeededRandomPool
- IV (Initialization Vector) randomization for each encryption
- Secure memory handling for sensitive data
- Proper cleanup of keys and IVs
- Input validation and error handling

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Author

Olutoye O
Contact: odufowokantoye@outlook.com

## Acknowledgments

- Crypto++ Library
- Modern C++ features
- CMake build system
