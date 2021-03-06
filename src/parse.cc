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

    std::vector<Node> vect;
    vect.reserve(size);
    unsigned cpt = 0; // Id
    while (std::getline(in, line))
    {
	    ++cpt;
        if (line[0] != c)
            continue;

        std::unordered_set<std::string> set;
        for (unsigned i = 2; i < line.size(); ++i)
        {
            while ((i < line.size() && is_separator(line[i]))
                                    || (line[i] >= '0' && line[i] <= '9'))
                ++i; // remove size and space

            std::string s;
            s.reserve(line.size() - i);
            while (i < line.size() && !is_separator(line[i]))
                s += line[i++];

            set.insert(s);
        }

        if (set.size() > 1) // remove input with X tags
            vect.push_back(Node(set, cpt - 1));
    }

    return vect;
}

int write_output(const std::string &out_path)
{
    return 0;
}

