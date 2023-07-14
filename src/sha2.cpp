
#include <iomanip>
#include <string>
#include <vector>

#include "../includes/sha2.hpp"


std::string sha256(std::string input)
{
    std::vector<unsigned char> message(input.begin(), input.end());

    // Get message size
    union 
    {
        std::uint64_t inInt64;
        unsigned char inChars[8];
    } messageSize;
    messageSize.inInt64 = message.size() * 8;

    // Pad message
    message.push_back(0x80);
    while (message.size() % 64 < 56)
    {
        message.push_back(0x00);
    }
    for (int i = 0; i < 8; i++)
    {
        message.push_back(messageSize.inChars[7-i]); // convert to big endian
    }

    std::uint32_t h0 = 0x6a09e667;
    std::uint32_t h1 = 0xbb67ae85;
    std::uint32_t h2 = 0x3c6ef372;
    std::uint32_t h3 = 0xa54ff53a;
    std::uint32_t h4 = 0x510e527f;
    std::uint32_t h5 = 0x9b05688c;
    std::uint32_t h6 = 0x1f83d9ab;
    std::uint32_t h7 = 0x5be0cd19;

    for (std::size_t i = 0; i < message.size(); i += 64)
    {
        std::uint32_t w[64];

        // Set the first 16 words as the chunk
        for (int j = 0; j < 16; j++)
        {
            union 
            {
                std::uint32_t asInt32;
                unsigned char asChars[4];
            } word;
            
            // Convert word data to big endian
            for (int k = 0; k < 4; k++)
            {
                word.asChars[k] = message[i + j*4 + (3-k)];
            }

            w[j] = word.asInt32;
        }

        // Generate the next 48 words
        for (int j = 16; j < 64; j++)
        {
            std::uint32_t s0 = rotr(w[j-15], 7) ^ rotr(w[j-15], 18) ^ (w[j-15] >> 3);
            std::uint32_t s1 = rotr(w[j-2], 17) ^ rotr(w[j-2], 19) ^ (w[j-2] >> 10);
            w[j] = w[j-16] + s0 + w[j-7] + s1;
        }

        std::uint32_t a = h0;
        std::uint32_t b = h1;
        std::uint32_t c = h2;
        std::uint32_t d = h3;
        std::uint32_t e = h4;
        std::uint32_t f = h5;
        std::uint32_t g = h6;
        std::uint32_t h = h7;

        for (int j = 0; j < 64; j++)
        {
            std::uint32_t S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
            std::uint32_t ch = (e & f) ^ ((~e) & g);
            std::uint32_t temp1 = h + S1 + ch + k[j] + w[j];

            std::uint32_t S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
            std::uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            std::uint32_t temp2 = S0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;

    }

    std::stringstream s;
    s << std::hex << std::setfill('0');
    for (const std::uint32_t* i: { &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7 })
    {
        s << std::setw(8) << *i;
    }
    return s.str();

}
