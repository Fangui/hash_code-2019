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
        if (!vect[n.scores[i].second].id)
        {
            dump(vect, vect[n.scores[i].second]);
            return;
        }
    }
    /*
    float score_max = 0.f;
    int id_max = -1;

    for (unsigned i = 0; i < n.scores.size(); ++i)
    {
        float score_cur = dump(vect, vect[n.scores[i].second], score + n.scores[i].first, n.scores[i].second);
        if (score_cur > score_max)
        {
            score_max = score_cur;
            id_max = vect[n.scores[i].second].id;
        }
    }
    if (id_max != -1)
        std::cout << id_max << '\n';
    return score + score_max;
    */
}

bool all_visited(const std::vector<Node> &vect)
{
    for (const auto &v :vect)
    {
        if (!v.used)
            return false;
    }
    return true;
}

void call_dump(std::vector<Node> &vect, unsigned idx)
{
    /*
    for (unsigned i = 0; i < vect.size(); ++i)
    {
        vect[i].used = false;
    }*/
    dump(vect, vect[idx]);
    //std::cout << total << '\n';
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

        for (unsigned j = 0; j < vect_h.size(); ++j)
        {
            if (j == i)
                continue;

            unsigned cpt = 0;
            const auto &set_j = vect_h[j].set;

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
            float score1 = cpt; // common tag
            float score2 = set_cur.size() - cpt; // in s1 no in s2
            float score3 = cpt2;               // in s2 no in s1

            auto &scores = vect_h[i].scores;
            float cur_score = std::min(score1, std::min(score2, score3));

            if (cur_score)
            {
                const unsigned nb_score = 20;
                if (vect_h[i].scores.size() < nb_score)
                    vect_h[i].scores.push_back(std::make_pair(cur_score, j));
                else
                {
                    sort(vect_h[i].scores.begin(), vect_h[i].scores.end(),
                            [](pair_v a, pair_v b) { return a.first > b.first; });

                    if (cur_score > vect_h[i].scores[nb_score - 1].first)
                        vect_h[i].scores[nb_score - 1] = std::make_pair(cur_score, j);
                }
            }
        }
    }



 //   call_dump(vect_h, b_idx);

    for (unsigned i = 0; i < vect_h.size(); ++i)
    {
        sort(vect_h[i].scores.begin(), vect_h[i].scores.end(),
                         [](pair_v a, pair_v b) { return a.first > b.first; });

    //    if (vect_h[i].scores.size() && vect_h[i].scores[0].first > 0.45)
      //      call_dump(vect_h, i);
    }

    sort(vect_h.begin(), vect_h.end(),
                   [](const Node &a, const Node &b) {
                   if (!a.scores.size() || !b.scores.size())
                   {
                       if (a.scores.size() && !b.scores.size())
                           return true;
                       else if (b.scores.size() && !a.scores.size())
                           return false;

                        return false;
                   }
                   return a.scores[0].first > b.scores[0].first; });

    /*
    for (unsigned i = 0; i < vect_h.size(); ++i)
    {
        if (vect_h[i].scores.size() && vect_h[i].scores[0].first > 0.49)
            call_dump(vect_h, i);

    }
    for (unsigned i = 0; i < vect_h.size(); ++i)
    {
        if (vect_h[i].scores.size() && vect_h[i].scores[0].first > 0.45)
            call_dump(vect_h, i);
    }
    for (unsigned i = 0; i < vect_h.size(); ++i)
    {
            if (vect_h[i].scores.size() && vect_h[i].scores[0].first > 0.3)
                call_dump(vect_h, i);
    }*/

    for (unsigned i = 0; i < vect_h.size(); ++i)
        call_dump(vect_h, i);

    return write_output("out");
}
