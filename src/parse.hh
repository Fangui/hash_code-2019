#pragma once

#include <vector>
#include <unordered_set>

struct Node
{
    Node(std::unordered_set<std::string> set, std::vector<float> score) :
        set (set), score (score) { }

    Node(std::unordered_set<std::string> set, unsigned size) :
        set (set)
    {
        score.reserve(size);
        for (unsigned i = 0; i < score.size(); ++i)
            score[i] = 0;
    }

    std::unordered_set<std::string> set;
    std::vector<float> score;
};

std::vector<Node> parse_input(const std::string &inp, char c);
int write_output(const std::string &out_path);
