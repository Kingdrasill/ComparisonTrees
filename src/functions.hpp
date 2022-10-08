#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "others.hpp"
#include <fstream>
#include <cstring>
#include <random>

typedef struct Times Times;

struct Times {
    std::vector<std::chrono::microseconds> insertion;
    std::vector<std::chrono::microseconds> search;
    std::vector<std::chrono::microseconds> remove;
};

void createFiles();
void readFiles();

#endif