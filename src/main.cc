#include <algorithm>
#include <iostream>
#include <functional>
//#include <parallel/algorithm>
#include <vector>

#include <cmath>
#include "parse.hh"

void dump(std::vector<Node> &vect, Node &n)
{
    if (n.used)
        return;

    n.used = true;

    std::cout << n.id << '\n';
    for (unsigned i = 0; i < n.scores.size(); ++i)
    {
        dump(vect, vect[n.idx[i]]);
    }
}


void call_dump(std::vector<Node> &vect, unsigned idx)
{
    dump(vect, vect[idx]);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }
    auto vect_h = parse_input(argv[1], 'H');
    //auto vect_v = parse_input(argv[1], 'V');


 //   std::cout << vect_h.size() << std::endl;
    unsigned b_idx = 0;
    float b_score = 0;

#pragma omp parallel for
    for (unsigned i = 0; i < vect_h.size(); ++i)
    {
        auto &set_cur = vect_h[i].set;
        unsigned cpt = 0;

        for (unsigned j = 0; j < vect_h.size(); ++j)
        {
            float delta = (float)vect_h[i].set.size() / (float)vect_h[j].set.size();
            if (delta < 0)
                delta = -delta;


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
            if (cur_score)
            {
                //vect_h[i].score = cur_score;
            //    vect_h[i].idx = i;
                vect_h[i].scores.push_back(cur_score);
                vect_h[i].idx.push_back(j);
#pragma omp critical
                {
                    if (cur_score > b_score)
                    {
                        b_idx = i;
                        b_score = cur_score;
                    }
                }
            }
        }
    }

    call_dump(vect_h, b_idx);


    for (unsigned i = 0; i < vect_h.size(); ++i)
        call_dump(vect_h, i);
    //std::cout << b_idx << std::endl;
    //std::cout << b_score << std::endl;
    return write_output("out");
}
