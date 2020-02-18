#include <algorithm>
#include <iostream>
#include <functional>
//#include <parallel/algorithm>
#include <vector>

#include <cmath>
#include "parse.hh"

unsigned compute_score(const std::unordered_set<int> &set_cur,
                       const std::unordered_set<int> &set_j)
{
    unsigned cpt = 0;

    for (const auto &str : set_cur)
    {
        if (set_j.find(str) != set_j.end()) //find
            ++cpt;
    }
    unsigned cpt2 = 0;
    for (const auto &str : set_j)
    {
        if (set_cur.find(str) == set_cur.end())
            ++cpt2;
    }
    unsigned score1 = cpt; // common tag
    unsigned score2 = set_cur.size() - cpt; // in s1 no in s2
    unsigned score3 = cpt2;               // in s2 no in s1

    return std::min(score1, std::min(score2, score3));
}

int nb_diff(std::unordered_set<int> &set_a,
              std::unordered_set<int> &set_b)
{
    int cpt = 0;
    for (const auto &str : set_a)
    {
        if (set_b.find(str) == set_b.end())
            ++cpt;
       // else
         //   --cpt;
    }

    return cpt;
}

void merge(std::vector<Node> &vect_h,
           std::vector<Node> &vect_v)
{
    sort(vect_v.begin(), vect_v.end(),
         [] (Node &a, Node &b) { return a.set.size() < b.set.size(); });

    while (vect_v.size())
    {
        size_t pos = 0;
        auto prev_node = vect_v[pos];
        vect_v.erase(vect_v.begin() + pos);

        int best_diff = -1000;
        for (size_t i = 0; i < vect_v.size(); ++i)
        {
            int cur_diff = nb_diff(prev_node.set, vect_v[i].set);

            if (cur_diff > best_diff)
            {
                best_diff = cur_diff;
                pos = i;
            }
        }

        prev_node.set.insert(vect_v[pos].set.begin(), 
                             vect_v[pos].set.end());

        prev_node.ids_.second = vect_v[pos].ids_.first;
        vect_v.erase(vect_v.begin() + pos);
        vect_h.push_back(prev_node);
    }

    /*
    for (unsigned i = 0; i < vect_v.size() / 2; ++i)
    {
        vect_v[i].ids_.second = vect_v[vect_v.size() - 1 - i].ids_.first;

        vect_v[i].set.insert(vect_v[vect_v.size() - 1 - i].set.begin(), 
                             vect_v[vect_v.size() - 1 - i].set.end());
        vect_h.push_back(vect_v[i]);
    }*/

    /*
    for (unsigned i = 0; i + 1 < vect_v.size(); i += 2)
    {
        vect_v[i].ids_.second = vect_v[i + 1].ids_.first;

        vect_v[i].set.insert(vect_v[i + 1].set.begin(), 
                             vect_v[i + 1].set.end());
        vect_h.push_back(vect_v[i]);
    }*/


    sort(vect_h.begin(), vect_h.end(),
         [] (Node &a, Node &b) { return a.set.size() < b.set.size(); });
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }
    auto vect_h = parse_input(argv[1], 'H');
    auto vect_v = parse_input(argv[1], 'V');

    merge(vect_h, vect_v);
    std::cout << vect_h.size() << '\n';

    size_t pos = 0;
    auto prev_node = vect_h[pos];

    size_t score_total = 0;

    std::cout << prev_node << '\n';
    vect_h.erase(vect_h.begin() + pos);

    while (vect_h.size())
    {
        int best_score = 0;
        auto best_node = vect_h[0];
        pos = 0;

//        std::cerr << vect_h.size() << std::endl;

#pragma omp parallel
        {
            int best_score_local = 0;
            auto best_node_local = vect_h[0];
            size_t pos_local = 0;

#pragma omp parallel for schedule (dynamic)
            for (size_t i = 0; i < vect_h.size(); ++i)
            {
                auto &cur_node = vect_h[i];

                if (cur_node.set.size() < 2 * (size_t)best_score)
                    continue;

                int cur_score = compute_score(cur_node.set, prev_node.set);

                if (cur_score > best_score_local)
                {
                    best_node_local = cur_node;
                    best_score_local = cur_score;
                    pos_local = i; 
                }
            }
#pragma omp critical
            {
                if (best_score_local > best_score)
                {
                    best_score = best_score_local;
                    best_node = best_node_local;
                    pos = pos_local;
                }
            }
        }

        std::cout << best_node << '\n';
        score_total += best_score;
        prev_node = best_node;
        vect_h.erase(vect_h.begin() + pos);
    }

    std::cerr << "score " << score_total << std::endl;
    return 0;
}
