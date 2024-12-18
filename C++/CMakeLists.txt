cmake_minimum_required(VERSION 3.10)

project(File-Encryption)

# Find Crypto++ using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(CRYPTOPP REQUIRED libcryptopp)  # Changed from libcrypto++ to libcryptopp

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
    ${CRYPTOPP_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(File-Encryption
    ${CRYPTOPP_LIBRARIES}
    stdc++fs
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
