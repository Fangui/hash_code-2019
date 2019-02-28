#include <iostream>
#include <fstream>
#include <sstream>

#include "parse.hh"

inline bool is_separator(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

void parse_input(const std::string &inp)
{
    std::ifstream in(inp);
    std::string str;
    std::string line;

    std::cout << "Read " << inp << '\n';
    while (std::getline(in, line))
    {
        for (unsigned i = 0; i < line.size(); ++i)
        {
            while (i < line.size() && is_separator(line[i]))
                ++i;

            std::string s;
            s.reserve(line.size() - i);
            while (i < line.size() && !is_separator(line[i]))
                s += line[i++];

            int val = stod(s);
            std::cout << val << "| ";
        }
        std::cout << '\n';
    }
}

int write_output(const std::string &out_path)
{
    std::ofstream out (out_path);

    if (out.is_open())
    {

        std::cout << "Write in : " << out_path << '\n';
    }
    else
    {
        std::cerr << "Error while writting in " << out_path << '\n';
        return 1;
    }

    return 0;
}

