#pragma once

#include <vector>
#include <unordered_set>

#include <iostream>

using pair_v = std::pair<unsigned, unsigned>;

struct Node
{

    Node(std::unordered_set<std::string> set, unsigned id) :
        set (set),
        id (id)
    {
        id_2 = -1;
        used = false;
    }

    std::unordered_set<std::string> set;
    unsigned id;
    int id_2;
    std::vector<pair_v> scores;
    bool used;
};

std::vector<Node> parse_input(const std::string &inp, char c);
int write_output(const std::string &out_path);
