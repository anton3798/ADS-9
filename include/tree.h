// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <string>

struct Node {
    char value;
    std::vector<Node*> children;
    explicit Node(char val) : value(val) {}
};
class PMTree {
 private:
    Node* root;
    std::vector<char> alphabet;
    void buildTree(Node* parent, std::vector<char> remaining);
    void deleteTree(Node* node);
    void collectPermutations(Node* node, std::vector<char>& current,
        std::vector<std::vector<char>>& result) const;

 public:
    explicit PMTree(const std::vector<char>& input);
    ~PMTree();
    Node* getRoot() const { return root; }
    std::vector<char> getAlphabet() const { return alphabet; }
    friend std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
    friend std::vector<char> getPerm1(const PMTree& tree, int num);
    friend std::vector<char> getPerm2(const PMTree& tree, int num);
};
std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
int factorial(int n);

#endif  // INCLUDE_TREE_H_
