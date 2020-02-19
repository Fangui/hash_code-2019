#include <iostream>
#include <fstream>
#include <sstream>

#include <unordered_set>
#include <unordered_map>

#include "parse.hh"

inline bool is_separator(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

std::unordered_map<int, std::vector<int>> Node::tags_to_id;

std::vector<Node> parse_input(const std::string &inp, char c, 
                              std::vector<Node *> &vect_pointer)
{
    std::ifstream in(inp);
    std::string str;
    std::string line;

    std::getline(in, line); // size
    unsigned size = stod(line);

    std::vector<Node> vect;
    vect.reserve(size);
    vect_pointer.reserve(size);

    while (vect_pointer.size() < size)
        vect_pointer.push_back(nullptr);

    static std::unordered_map<std::string, int> tags;

    int id_photo = -1;
    static int id_tags = 0;


    while (std::getline(in, line))
    {
        ++id_photo;
        if (line[0] != c)
            continue;

        std::unordered_set<int> set;

        for (unsigned i = 2; i < line.size(); ++i)
        {
            while ((i < line.size() && is_separator(line[i]))
                                    || (line[i] >= '0' && line[i] <= '9'))
                ++i; // remove size and space

            std::string s;
            s.reserve(line.size() - i);
            while (i < line.size() && !is_separator(line[i]))
                s += line[i++];

            auto it = tags.find(s);
            if (it == tags.end())
            {
                tags.emplace(s, id_tags++);
                it = tags.find(s);
            }

            set.emplace(it->second); // it->second = id of tags
            auto iterator = Node::tags_to_id.find(it->second);

            if (iterator == Node::tags_to_id.end())
                Node::tags_to_id.emplace(it->second, std::vector<int>{id_photo}); // add picture to the vector
            else
                iterator->second.push_back(id_photo);
        }

//        if (set.size() > 1) // remove input with X tags
        vect.push_back(Node(set, id_photo));
        vect_pointer[id_photo] = &(vect[vect.size() - 1]);
    }

    return vect;
}
