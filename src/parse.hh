#pragma once

#include <vector>
#include <unordered_set>

struct Node
{

    Node(std::unordered_set<std::string> set) :
        set (set)
    {
        score = 0;
    }

    std::unordered_set<std::string> set;
    float score;
};

std::vector<Node> parse_input(const std::string &inp, char c);
int write_output(const std::string &out_path);
