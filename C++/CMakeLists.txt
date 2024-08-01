# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(FileEncryption)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
add_executable(FileEncrypt main.cpp)

# Ensure you have only one definition of this target
add_executable(main.cpp Encryption.cpp Uppercase.cpp Copy.cpp)

# Include directories (if you have headers in a separate directory)
# target_include_directories(MyExecutable PRIVATE include)

# Link libraries (if your project depends on external libraries)
# target_link_libraries(MyExecutable PRIVATE mylibrary)
