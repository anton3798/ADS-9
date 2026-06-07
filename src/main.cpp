// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <cstdio>
#include "tree.h"

void printPermutation(const std::vector<char>& perm) {
    for (char c : perm) std::cout << c;
}
template<typename Func>
double measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

int main() {
  setlocale(LC_ALL, "Russian");
std::vector<char> alphabet1 = { '1', '2', '3' };
PMTree tree1(alphabet1);

std::cout << "\nАлфавит: {1,2,3}\n";
std::cout << "Все перестановки getAllPerms:\n";
auto all1 = getAllPerms(tree1);
for (size_t i = 0; i < all1.size(); ++i) {
    std::cout << "  " << (i + 1) << ": ";
    printPermutation(all1[i]);
    std::cout << "\n";
}
std::cout << "\nПерестановка 1 getPerm1: ";
printPermutation(getPerm1(tree1, 1));
std::cout << "\nПерестановка 2 getPerm2: ";
printPermutation(getPerm2(tree1, 2));
std::cout << "\n";
std::ofstream out("result/experiment_results.csv");
out << "n;getAllPerms;getPerm1;getPerm2\n";
std::random_device rd;
std::mt19937 gen(rd());
std::cout << "\n";
std::cout << " n | getAllPerms (мс) | getPerm1 (мс) | getPerm2 (мс)\n";
for (int n = 2; n <= 9; ++n) {
    std::vector<char> alphabet;
    for (int i = 0; i < n; ++i) alphabet.push_back('1' + i);
    PMTree tree(alphabet);
    double tAll = measureTime([&]() { getAllPerms(tree); });
    int total = 1;
    for (int i = 2; i <= n; ++i) total *= i;
    std::uniform_int_distribution<> dis(1, total);
    int rndNum = dis(gen);
    double t1 = measureTime([&]() { getPerm1(tree, rndNum); });
    double t2 = measureTime([&]() { getPerm2(tree, rndNum); });
    printf("%2d | %15.6f | %12.6f | %12.6f\n", n, tAll, t1, t2);
    out << n << ";" << tAll << ";" << t1 << ";" << t2 << "\n";
}
out.close();
  return 0;
}
