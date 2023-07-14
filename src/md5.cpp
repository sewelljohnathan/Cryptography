
#include <iomanip>
#include <string>
#include <vector>

#include "../includes/md5.hpp"


std::string md5(std::string input)
{
    // Set message
    std::vector<char> message(input.begin(), input.end());

    // Get original message size
    std::size_t messageSize = message.size() * 8;
    char* messageSizeInChars = reinterpret_cast<char*>(&messageSize);
    
    // Pad
    message.push_back(0x80);
    while (message.size() % 64 < 56) 
    {
        message.push_back(0x00);
    }

    // Add original size
    for (int i = 0; i < 8; i++)
    {
        message.push_back(messageSizeInChars[i]);
    }

    // Primary algo
    std::uint32_t a0 = 0x67452301;
    std::uint32_t b0 = 0xefcdab89;
    std::uint32_t c0 = 0x98badcfe;
    std::uint32_t d0 = 0x10325476;

    for (std::size_t i = 0; i < message.size(); i += 64)
    {   
        
        // Get the current chunk
        std::uint32_t* M;
        char chunkInChars[64];
        for (int j = 0; j < 64; j++)
        {
            chunkInChars[j] = message.at(i + j);
        }
        M = reinterpret_cast<std::uint32_t*>(chunkInChars);

        // Algo
        std::uint32_t A = a0;
        std::uint32_t B = b0;
        std::uint32_t C = c0;
        std::uint32_t D = d0;

        for (int j = 0; j < 64; j++)
        {
            std::uint32_t F, g;
            if (j < 16)
            {
                F = (B & C) | ((~B) & D);
                g = j;
            }
            else if (j < 32)
            {
                F = (D & B) | ((~D) & C);
                g = (5*j + 1) % 16;
            }
            else if (j < 48)
            {
                F = B ^ C ^ D;
                g = (3*j + 5) % 16;
            }
            else if (j < 64)
            {
                F = C ^ (B | (~D));
                g = (7*j) % 16;
            }

            F = F + A + K[j] + M[g];
            A = D;
            D = C;
            C = B;
            B = B + rotl(F, s[j]);
        }

        a0 += A;
        b0 += B;
        c0 += C;
        d0 += D;
    }

    // Flip bytes
    std::stringstream s;
    s << std::hex << std::setfill('0');
    for (const std::uint32_t* i : { &a0, &b0, &c0, &d0 })
    {
        std::uint32_t flipped = ((*i) >> 24) | (((*i) & 0x00FF0000) >> 8) | (((*i) & 0x0000FF00) << 8) | ((*i) << 24);
        s << std::setw(8) << flipped;
    }
    return s.str();
}