#include <iostream>
#include <fstream>
#include <iterator>

#include "Person_generated.h"
#include "Book_generated.h"

Occupation from_string(std::string s)
{
    decltype(EnumValuesOccupation()) values = EnumValuesOccupation();

    for (Occupation o : values)
    {
        if (s == EnumNameOccupation(o))
            return o;
    }

    throw std::invalid_argument("'" + s + "' not in enum values set");
}

flatbuffers::DetachedBuffer CreateBookBuffer(std::string name,
                                       std::string datePublished)
{
    flatbuffers::FlatBufferBuilder fbb;

    auto oBook = CreateBook(fbb, fbb.CreateString(name.c_str()),
               fbb.CreateString(datePublished.c_str()));

    fbb.Finish(oBook);
    return fbb.Release();
}

int main(int argc, char** argv)
try
{
    using namespace flatbuffers;

    std::ifstream is(argv[1]);
    std::string name, lastname, occStr, bookName, bookDatePublished;

    is >> name >> lastname >> occStr >> bookName >> bookDatePublished;

    flatbuffers::FlatBufferBuilder fbb;

    Occupation occ = from_string(occStr);

    Offset<Vector<uint8_t>> oBook{};

    if (!bookName.empty() && !bookDatePublished.empty())
    {
        auto bookBuf = CreateBookBuffer(bookName, bookDatePublished);
        oBook = fbb.CreateVector(bookBuf.data(), bookBuf.size());
    }

    auto oPerson = CreatePerson(fbb, fbb.CreateString(name.c_str()),
                 fbb.CreateString(lastname.c_str()), occ, oBook);

    fbb.Finish(oPerson);
    auto buf = fbb.Release();

    std::ofstream os("person.bin");

    os.write(reinterpret_cast<char*>(buf.data()), buf.size());
}
catch(const std::invalid_argument &ia)
{
    std::cerr << "invalid_argument: " << ia.what() << '\n';
    return 1;
}
