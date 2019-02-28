#include <iostream>
#include <fstream>
#include <sstream>

#include <unordered_set>

#include "parse.hh"


inline bool is_separator(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

std::vector<Node> parse_input(const std::string &inp, char c)
{
    std::ifstream in(inp);
    std::string str;
    std::string line;

    std::getline(in, line); // size
    unsigned size = stod(line);

  //  std::cout << "Read " << inp << '\n';
    std::vector<Node> vect;
    vect.reserve(size);
    while (std::getline(in, line))
    {
        if (line[0] != c)
            continue;

        std::unordered_set<std::string> set(50);
        for (unsigned i = 2; i < line.size(); ++i)
        {
            while ((i < line.size() && is_separator(line[i])) || (line[i] >= '0' && line[i] <= '9'))
                ++i;

            std::string s;
            s.reserve(line.size() - i);
            while (i < line.size() && !is_separator(line[i]))
                s += line[i++];

            set.insert(s);
        }
        vect.push_back(Node(set, size));
    }

    return vect;
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

