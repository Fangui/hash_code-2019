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
        dump(vect, vect[n.scores[i].second]);
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


   // unsigned b_idx = 0;
   // float b_score = 0;

#pragma omp parallel for schedule (dynamic)
    for (unsigned i = 0; i < vect_h.size(); ++i)
    {
        auto &set_cur = vect_h[i].set;
        unsigned cpt = 0;

        for (unsigned j = i + 1; j < vect_h.size(); ++j)
        {
            auto &set_j = vect_h[j].set;
            for (const auto &str : set_cur)
            {
                if (set_j.find(str) != set_j.end()) //find
                    ++cpt;
            }

            auto &scores = vect_h[i].scores;
            float cur_score = (float)cpt / (float)(set_j.size());
            if (cur_score > 0.5)
                cur_score = 0.5 - (cur_score - 0.5);

            if (cur_score)
            {
                const unsigned nb_score = 20; 
                if (vect_h[i].scores.size() < nb_score)
                    vect_h[i].scores.push_back(std::make_pair(cur_score, j));
                else
                {
                    if (cur_score > vect_h[i].scores[nb_score - 1].first)
                    {
                        vect_h[i].scores[nb_score - 1] = std::make_pair(cur_score, j);
                        sort(vect_h[i].scores.begin(), vect_h[i].scores.end(),
                         [](pair_v a, pair_v b) { return a.first > b.first; });
                        
                    }
                }
            }
        }
    }

 //   call_dump(vect_h, b_idx);

    for (unsigned i = 0; i < vect_h.size(); ++i)
    {
        sort(vect_h[i].scores.begin(), vect_h[i].scores.end(),
                         [](pair_v a, pair_v b) { return a.first > b.first; });

        if (vect_h[i].scores.size() && vect_h[i].scores[0].first > 0.45)
            call_dump(vect_h, i);
    }

    for (unsigned i = 0; i < vect_h.size(); ++i)
    {
        sort(vect_h[i].scores.begin(), vect_h[i].scores.end(),
                         [](pair_v a, pair_v b) { return a.first > b.first; });

        if (vect_h[i].scores.size() && vect_h[i].scores[0].first > 0.4)
            call_dump(vect_h, i);
    }

    for (unsigned i = 0; i < vect_h.size(); ++i)
    {
            if (vect_h[i].scores.size() && vect_h[i].scores[0].first > 0.3)
                call_dump(vect_h, i);
    }

    for (unsigned i = 0; i < vect_h.size(); ++i)
        call_dump(vect_h, i);

    return write_output("out");
}
