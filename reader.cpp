#include <iostream>
#include <fstream>
#include <vector>

#include "Person_generated.h"

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

    if (!VerifyPersonBuffer(vrfr))
    {
        std::cerr << "Invalid input buffer\n";
        std::exit(1);
    }

    auto pPerson = GetPerson(buf.data());

    std::cout << pPerson->name()->c_str() << ' ' << pPerson->lastname()->c_str()
              << ' ' << EnumNameOccupation(pPerson->occupation()) << '\n';

    switch(pPerson->occupation())
    {
        case Occupation::Unoccupied:
            std::cout << "Go get yourself a job\n"; break;
        case Occupation::Worker:
            std::cout << "Work harder\n"; break;
        case Occupation::Writer:
            std::cout << "Sell a book\n"; break;
        case Occupation::Developer:
            std::cout << "God bless you\n"; break;
        case Occupation::Doctor:
            std::cout << "Cure my disease\n"; break;
        default:
            std::cout << "I dunnow\n";
    }
}
