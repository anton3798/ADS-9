// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& input) {
    alphabet = input;
    root = new Node('R');
    if (!input.empty()) {
        buildTree(root, input);
    }
}
PMTree::~PMTree() {
    deleteTree(root);
}

void PMTree::deleteTree(Node* node) {
    if (node == nullptr) return;
    for (Node* child : node->children) {
        deleteTree(child);
    }
    delete node;
}

void PMTree::buildTree(Node* parent, std::vector<char> remaining) {
    if (remaining.empty()) {
        return;
    }
    for (char c : remaining) {
        Node* child = new Node(c);
        parent->children.push_back(child);
        std::vector<char> new_remaining;
        for (char x : remaining) {
            if (x != c) {
                new_remaining.push_back(x);
            }
        }
        buildTree(child, new_remaining);
    }
}

void PMTree::collectPermutations(Node* node, std::vector<char>& current,
    std::vector<std::vector<char>>& result) {
    if (node->value != 'R') {
        current.push_back(node->value);
    }
    if (node->children.empty()) {
        if (!current.empty()) {
            result.push_back(current);
        }
    } else {
        for (Node* child : node->children) {
            collectPermutations(child, current, result);
        }
    }
    if (node->value != 'R') {
        current.pop_back();
    }
}

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    const_cast<PMTree&>(tree).collectPermutations(tree.root, current, result);
    return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    std::vector<std::vector<char>> all_perms = getAllPerms(tree);
    if (num < 1 || num > all_perms.size()) {
        return std::vector<char>();
    }
    return all_perms[num - 1];
}

void navigateTree(Node* node, int& remaining_num, std::vector<char>& result) {
    if (node == nullptr || node->children.empty()) {
        return;
    }
    if (node->value != 'R') {
        result.push_back(node->value);
    }
    if (node->children.size() == 1) {
        navigateTree(node->children[0], remaining_num, result);
        return;
    }
    int perms_per_child = factorial(node->children.size() - 1);
    for (int i = 0; i < node->children.size(); i++) {
        if (remaining_num <= perms_per_child) {
            navigateTree(node->children[i], remaining_num, result);
            return;
        } else {
            remaining_num -= perms_per_child;
        }
    }
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    int total_perms = factorial(tree.alphabet.size());
    if (num < 1 || num > total_perms) {
        return std::vector<char>();
    }
    std::vector<char> result;
    int remaining_num = num;
    navigateTree(tree.root, remaining_num, result);
    return result;
}
