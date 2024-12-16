cmake_minimum_required(VERSION 3.10)

project(File-Encryption)

# Add source files
add_executable(File-Encryption
    main.cpp
    src/Utils.cpp
)

# Add include directory
target_include_directories(File-Encryption PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

target_link_libraries(File-Encryption cryptopp)
