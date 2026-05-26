// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
 public:
    struct Node {
        char value;
        std::vector<std::shared_ptr<Node>> children;
        explicit Node(char v) : value(v) {}
        Node() : value(0) {}
    };

    std::shared_ptr<Node> root;
    int n;

    explicit PMTree(const std::vector<char>& in) {
        root = std::make_shared<Node>();
        n = static_cast<int>(in.size());
        std::vector<char> sorted = in;
        std::sort(sorted.begin(), sorted.end());
        build(root, sorted);
    }

 private:
    void build(std::shared_ptr<Node> node, const std::vector<char>& items) {
        for (size_t i = 0; i < items.size(); ++i) {
            auto child = std::make_shared<Node>(items[i]);
            node->children.push_back(child);
            std::vector<char> rest;
            rest.reserve(items.size() - 1);
            for (size_t j = 0; j < items.size(); ++j) {
                if (j != i) rest.push_back(items[j]);
            }
            build(child, rest);
        }
    }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
