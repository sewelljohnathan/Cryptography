
#include <iostream>

#include "../includes/md5.hpp"
#include "../includes/sha2.hpp"

int main(void)
{
    std::cout << md5("The quick brown fox jumps over the lazy dog") << std::endl;
    std::cout << sha256("The quick brown fox jumps over the lazy dog") << std::endl;
}
