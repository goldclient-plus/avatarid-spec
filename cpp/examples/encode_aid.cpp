//-----------------------------------------------------------------------------
// File: examples/encode_aid.cpp
// Purpose: Minimal example demonstrating encoding and decoding of avatar hashes
//          using a GoldSrc-safe custom Base85 alphabet for the *aid system.
//-----------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "../base64.h"

std::string BytesToHexString(const uint8_t *data, size_t size)
{
    const char hexChars[] = "0123456789abcdef";
    std::string out;
    out.resize(size * 2);

    for (size_t i = 0; i < size; ++i)
    {
        uint8_t byte = data[i];
        out[2 * i]     = hexChars[byte >> 4];
        out[2 * i + 1] = hexChars[byte & 0x0F];
    }

    return out;
}

int main()
{
    // Example binary avatar id (9 bytes)
    uint8_t raw_aid[] =
    {
        0x96, // 150 revision
        0x46, 0xe9, 0x99, 0x8a, 0x32, 0x85, 0x53, 0x3a // 8 bytes unique user hash
    };

    // Encode
    uint32_t encode_size = base64::GetEncodeMaxOutput(sizeof(raw_aid));

    std::string encoded;
    encoded.resize(encode_size);

    if (!base64::Encode(raw_aid, sizeof(raw_aid), &encoded[0], &encode_size))
    {
        std::cerr << "Encoding failed!" << std::endl;
        return 1;
    }

    encoded.resize(encode_size);

    std::cout << "*aid encoded hash: " << encoded << std::endl;

    // Decode
    uint32_t decode_size = base64::GetDecodeMaxOutput(encoded.size());
    std::vector<uint8_t> decoded(decode_size);

    if (!base64::Decode(encoded.c_str(), encoded.size(), decoded.data(), &decode_size))
    {
        std::cerr << "Decoding failed!" << std::endl;
        return 1;
    }

    decoded.resize(decode_size);

    // Simple test
    // Check whether the decoded result matches the original one

    // revision
    if (decoded[0] != raw_aid[0])
    {
        std::cerr << "Decoded revision does not match original! (Encoding issue)" << std::endl;
        return 1;
    }

    // unique user hash
    if (memcmp(decoded.data() + 1, raw_aid + 1, decoded.size() - 1) != 0)
    {
        std::cerr << "Decoded user hash does not match original! (Encoding issue)" << std::endl;
        return 1;
    }

    std::string hexHash = BytesToHexString(decoded.data() + 1, decoded.size() - 1);
    std::cout << "Decoded revision: " << static_cast<int>(decoded[0]) << std::endl;
    std::cout << "Decoded hash string: " << hexHash << std::endl;

    return 0;
}
