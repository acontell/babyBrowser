#ifndef NODE_HPP
#define NODE_HPP

#include<string>

struct Node {
    std::string tag, content;

    Node(std::string t) : tag(std::move(t)) {
    }
};


#endif /* NODE_HPP */
