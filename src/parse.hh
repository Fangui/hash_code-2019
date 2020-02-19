#pragma once

#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <iostream>

using pair_v = std::pair<unsigned, unsigned>;

struct Node
{

    Node(std::unordered_set<int> set, int id) :
        set (set)
    {
        ids_.first = id;
        ids_.second = -1;
        used = false;
    }

    friend std::ostream& operator<<(std::ostream &out, const Node& node);

    static std::unordered_map<int, std::vector<int>> tags_to_id;

    bool used;
    std::unordered_set<int> set;
    std::pair<int, int> ids_;
};

inline std::ostream& operator<<(std::ostream &out, const Node& node)
{
    out << node.ids_.first;

    if (node.ids_.second != -1)
        out << " " << node.ids_.second;
    return out;
}

std::vector<Node> parse_input(const std::string &inp, char c, 
                              std::vector<Node *> &vect_pointer);
