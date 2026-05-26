// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <vector>
#include <memory>
#include <algorithm>
#include "tree.h"

static void collect(const std::shared_ptr<PMTree::Node>& node,
                    std::vector<char>& current,
                    std::vector<std::vector<char>>& result) {
    if (node->children.empty()) {
        if (!current.empty()) result.push_back(current);
        return;
    }
    for (const auto& child : node->children) {
        current.push_back(child->value);
        collect(child, current, result);
        current.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    if (tree.root) collect(tree.root, current, result);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    std::vector<std::vector<char>> all = getAllPerms(tree);
    if (num < 1 || num > static_cast<int>(all.size())) return {};
    return all[num - 1];
}

static int factorial(int k) {
    int r = 1;
    for (int i = 2; i <= k; ++i) r *= i;
    return r;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    int total = factorial(tree.n);
    if (num < 1 || num > total) return {};

    std::vector<char> result;
    auto node = tree.root;
    int idx = num - 1;
    int remaining = tree.n;

    while (remaining > 0) {
        int blockSize = factorial(remaining - 1);
        int childIndex = idx / blockSize;
        idx = idx % blockSize;
        if (childIndex < 0 ||
            childIndex >= static_cast<int>(node->children.size())) {
            return {};
        }
        node = node->children[childIndex];
        result.push_back(node->value);
        remaining--;
    }
    return result;
}
