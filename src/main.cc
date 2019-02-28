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
    auto vect_h = parse_input(argv[1], 'H');
    auto vect_v = parse_input(argv[1], 'V');

    std::cout << vect_h.size() << std::endl;

#pragma omp parallel for 
    for (unsigned i = 0; i < vect_h.size(); ++i)
    {
        auto &set_cur = vect_h[i].set;
        unsigned cpt = 0;

        for (unsigned j = 0; j < vect_h.size(); ++j)
        {
            if (i != j)
            {
                auto &set_j = vect_h[j].set;
                for (const auto &str : set_cur)
                {
                    if (set_j.find(str) != set_j.end()) //find
                        ++cpt;
                }
            }

            float cur_score = (float)cpt / (float)(vect_h.size());
            if (cur_score > vect_h[i].score)
            {
                vect_h[i].score = cur_score;
            }
        }
    }

    return write_output("out");
}
