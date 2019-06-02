#include <iostream>
#include <fstream>
#include <vector>

#include "Book_generated.h"

std::vector<uint8_t> read(std::string filePath)
{
    std::ifstream is(filePath);

    if (!is)
    {
        std::cerr << "File '" << filePath << "' not found\n";
        std::exit(1);
    }

    is >> std::noskipws;

    std::vector<uint8_t> buf(std::istream_iterator<uint8_t>{is},
                             std::istream_iterator<uint8_t>{});

    return buf;
}

int main(int argc, char **argv)
{
    auto buf = read(argv[1]);

    flatbuffers::Verifier vrfr(buf.data(), buf.size());

    if (!VerifyBookBuffer(vrfr))
    {
        std::cerr << "Invalid input buffer\n";
        std::exit(1);
    }

    auto pBook = GetBook(buf.data());

    std::cout << pBook->name()->c_str() << ' '
              << pBook->datePublished()->c_str() << '\n';
}
