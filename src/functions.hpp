#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "others.hpp"
#include <fstream>
#include <cstring>
#include <random>

typedef struct StructTimes StructTimes;
typedef struct Times Times;

struct StructTimes {
    std::vector<std::chrono::microseconds> insertion;
    std::vector<std::chrono::microseconds> search;
    std::vector<std::chrono::microseconds> remove;
};

struct Times {
    StructTimes binaryTree;
    StructTimes avlTree;
    StructTimes redblackTree;
    StructTimes vetorTimes;
    StructTimes mapTimes;
    StructTimes unomapTimes;
};

void createFiles();
void readFiles(std::vector<Times> *tempos);
void createTimeFile(std::vector<Times> tempos, int n);

void fillFileWithTime(Times tempos, int tipo, std::fstream *file);
void fillFileWithAverageTime(std::vector<Times> tempos, int n, int tipo, std::fstream *file);
double timeToMiliseconds(Times tempos, int estrutura, int tipo, int size);
double averageTimeToMiliseconds(std::vector<Times> tempos, int n, int estrutura, int tipo, int size);

#endif