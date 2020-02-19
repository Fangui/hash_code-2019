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
           std::vector<Node> &vect_v,
           std::vector<Node *> &vect_pointer)
{
    auto copy_vect(vect_v);
    
    sort(copy_vect.begin(), copy_vect.end(),
         [] (Node &a, Node &b) { return a.set.size() < b.set.size(); });

    /*
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
                             vect_v[pos].set.end()); // merge verticaux
        prev_node.ids_.second = vect_v[pos].ids_.first;

        *vect_pointer[prev_node.ids_.second] = prev_node;
        vect_h.push_back(prev_node);

        vect_pointer[prev_node.ids_.first] = &(vect_h[vect_h.size() - 1]);
        vect_pointer[prev_node.ids_.second] = &(vect_h[vect_h.size() - 1]);
    }*/

    for (auto i = 0u; i + 1 < copy_vect.size(); i += 2)
    {
        auto merge = copy_vect[i];
        merge.ids_.second = copy_vect[i + 1].ids_.first;
        merge.set.insert(copy_vect[i + 1].set.begin(),
                         copy_vect[i + 1].set.end());

        vect_h.push_back(merge);
        vect_pointer[merge.ids_.first] = &(vect_h[vect_h.size() - 1]);
        vect_pointer[merge.ids_.second] = &(vect_h[vect_h.size() - 1]);

    }

//    sort(vect_h.begin(), vect_h.end(),
  //       [] (Node &a, Node &b) { return a.set.size() < b.set.size(); });
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    std::vector<Node *> vect_pointer;
    
    auto vect_h = parse_input(argv[1], 'H', vect_pointer);
    auto vect_v = parse_input(argv[1], 'V', vect_pointer);

    merge(vect_h, vect_v, vect_pointer);
    std::cerr << "merge finish" << std::endl;
    std::cout << vect_h.size() << '\n';

    size_t pos = 0;
    auto prev_node = vect_h[pos];
    vect_pointer[pos]->used = true;

    size_t score_total = 0;

    std::cout << prev_node << '\n';

    for (size_t j = 0; j < vect_h.size() - 1; ++j)
    {
        size_t best_score = 0;
        auto best_node = vect_h[0];
        size_t i = 0;

        for (const auto &id_tags : prev_node.set)
        {
            auto it = Node::tags_to_id.find(id_tags);
            if (it == Node::tags_to_id.end())
                continue;

            for (const auto id_photo : it->second)
            {
                auto &cur_node = *(vect_pointer[id_photo]);
                if (cur_node.used || (size_t)best_score > 2 * cur_node.set.size())
                    continue;

                auto cur_score = compute_score(prev_node.set, cur_node.set);

                if (cur_score > best_score)
                {
                    best_score = cur_score;
                    best_node = cur_node;
                }
            }
            ++i;
        }

        if (best_node.used)
        {
            for (const auto &it : vect_h)
            {
                if (!it.used)
                {
                    best_node = it;
                    break;
                }
            }
        }
        prev_node = best_node;

        vect_pointer[prev_node.ids_.first]->used = true;
        if (prev_node.ids_.second != -1)
            vect_pointer[prev_node.ids_.second]->used = true;

        std::cout << prev_node << '\n';
        score_total += best_score;
    }

    /*
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
    */

    std::cerr << "score " << score_total << std::endl;
    return 0;
}
