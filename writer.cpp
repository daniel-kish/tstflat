#include <iostream>
#include <fstream>
#include <iterator>

#include "Person_generated.h"

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

int main(int argc, char** argv)
try{
    std::ifstream is(argv[1]);
    std::string name, lastname, occStr;

    is >> name >> lastname;
    is >> occStr;

    flatbuffers::FlatBufferBuilder fbb;

    Occupation occ = from_string(occStr);

    auto oPerson = CreatePerson(fbb, fbb.CreateString(name.c_str()),
                 fbb.CreateString(lastname.c_str()), occ);

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
