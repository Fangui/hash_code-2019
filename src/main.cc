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

    std::cout << n.id;
    if (n.id_2 != -1) // vertical
        std::cout << ' ' << n.id_2;
    std::cout << '\n';

    for (unsigned i = 0; i < n.scores.size(); ++i)
    {
        if (!vect[n.scores[i].second].used)
        {
            dump(vect, vect[n.scores[i].second]);
            return;
        }
    }
}

unsigned node_left(const std::vector<Node> &vect)
{
    unsigned cpt = 0;
    for (const auto &v :vect)
    {
        if (!v.used)
            ++cpt;
    }
    return cpt;
}

void call_dump(std::vector<Node> &vect, unsigned idx)
{
    dump(vect, vect[idx]);
}

unsigned compute_score(const std::unordered_set<std::string> &set_cur,
                       const std::unordered_set<std::string> &set_j)
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

int nb_commun(std::unordered_set<std::string> &set_a,
                   std::unordered_set<std::string> &set_b)
{
    int cpt = 0;
    for (const auto &str : set_a)
    {
        if (set_b.find(str) == set_b.end())
            ++cpt;
        else
            --cpt;
    }

    return cpt;
}

void merge(std::vector<Node> &vect_h,
           std::vector<Node> &vect_v)
{
    sort(vect_v.begin(), vect_v.end(),
         [] (Node &a, Node &b) { return a.set.size() < b.set.size(); });

    for (unsigned i = 0; i < vect_v.size() / 2; ++i)
    {
        vect_v[i].id_2 = vect_v[vect_v.size() - 1 - i].id;

        for (const auto &str : vect_v[vect_v.size() - 1 - i].set)
            vect_v[i].set.insert(str);

        vect_h.push_back(vect_v[i]);
    }

    /*
    for (unsigned i = 0; i < vect_v.size(); ++i)
    {
        unsigned b_idx = 0;
        int b_commun = -1000;

        #pragma omp parallel for
        for (unsigned j = vect_v.size() * 0.95; j < vect_v.size(); ++j)
        {
            if (i == j)
                continue;
            int commun = nb_commun(vect_v[i].set, vect_v[j].set);
            if (b_commun == -1000 || b_commun > commun) // store the minimum
            {
                #pragma omp critical
                {
                    b_commun = commun;
                    b_idx = j;
                }
            }
        }

        for (const auto &str : vect_h[b_idx].set)
            vect_v[i].set.insert(str);

        vect_v[i].id_2 = vect_v[b_idx].id;

        vect_h.push_back(vect_v[i]);
        vect_v.erase(vect_v.begin() + b_idx);
        vect_v.erase(vect_v.begin() + i);
        i -= 1;
    }*/
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
    const unsigned nb_score = 1800; // nb score store

#pragma omp parallel for schedule (dynamic)
    for (unsigned i = 0; i < vect_h.size(); ++i)
    {
        for (unsigned j = 0; j < vect_h.size(); ++j)
        {
            if (j == i)
                continue;

            unsigned cur_score = compute_score(vect_h[i].set, vect_h[j].set);


            /*

            if (!cur_score)
                continue;
*/
            if ( (float)cur_score / (float)vect_h[i].set.size() < 0.1)
                continue;

            auto &scores = vect_h[i].scores;

            if (scores.size() < nb_score // insert if buffer not fill or if better score
                 || cur_score > scores[scores.size() - 1].first)
            {
                auto pair = std::make_pair(cur_score, j);
                scores.insert(std::upper_bound(scores.begin(), scores.end(),
                              pair,
                            [](pair_v a, pair_v b) { return a.first > b.first; }), pair);

                if (scores.size() > nb_score)
                    scores.pop_back();
            }
        }
    }

    unsigned not_used_prev = node_left(vect_h);
    for (unsigned j = 0; j < 100; ++j)
    {
        unsigned b_idx = 0;
        float b_score = 0;
        for (unsigned i = 0; i < vect_h.size(); ++i)
        {
            if (vect_h[i].scores.size() && !vect_h[i].used
                                        && vect_h[i].scores[0].first > b_score)
            {
                b_score = vect_h[i].scores[0].first;
                b_idx = i;
            }
        }
        call_dump(vect_h, b_idx);

        unsigned not_used = node_left(vect_h);
        if (!not_used || not_used == not_used_prev)
            break;

        not_used_prev = not_used;
    }

    for (unsigned i = 0; i < vect_h.size(); ++i)
        call_dump(vect_h, i);

    return write_output("out");
}
