cmake_minimum_required(VERSION 3.10)

project(File-Encryption)

# Add source files
add_executable(File-Encryption
    main.cpp
    src/Utils.cpp
    src/Encryption.cpp
    src/Decryption.cpp
)

# Add include directory
target_include_directories(File-Encryption PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

# Find and link Crypto++
find_package(CryptoPP REQUIRED)
target_link_libraries(File-Encryption
    cryptopp
    stdc++fs  # For filesystem support
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
