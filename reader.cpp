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

    switch(pPerson->occupation())
    {
        case Occupation::Unoccupied:
            std::cout << "Go get yourself a job"; break;
        case Occupation::Worker:
            std::cout << "Work harder"; break;
        case Occupation::Writer:
            std::cout << "Sell a book"; break;
        case Occupation::Developer:
            std::cout << "Go write some code"; break;
        case Occupation::Doctor:
            std::cout << "Go cure people"; break;
        default:
            std::cout << "I don't know how to process occupation '"
                      << static_cast<int>(pPerson->occupation()) << "'\n";
            std::exit(2);
    }

    std::cout << ", " << EnumNameOccupation(pPerson->occupation()) << ' '
              << pPerson->name()->c_str() << ' '
              << pPerson->lastname()->c_str() << '\n';

    if (pPerson->book())
    {
        std::cout << "'book' buffer (" << pPerson->book()->size() << " bytes)";

        std::ofstream os("book.bin");

        os.write(reinterpret_cast<const char *>(pPerson->book()->data()),
                 pPerson->book()->size());
    }

    std::cout << '\n';

}
