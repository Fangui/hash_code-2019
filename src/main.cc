#include <algorithm>
#include <iostream>
#include <functional>
//#include <parallel/algorithm>
#include <vector>

#include "parse.hh"

using pair_v = std::pair<char, int>;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage : " << argv[0] << " inputfile outputfile" << '\n';
        return 1;
    }
    parse_input(argv[1]);

    return write_output("out");
}
