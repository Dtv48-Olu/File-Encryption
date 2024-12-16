// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <string>

void initializeKeyAndIV(CryptoPP::byte* key, CryptoPP::byte* iv);

#endif
