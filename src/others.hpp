#ifndef OTHERS_HPP
#define OTHERS_HPP

#include "redblack.hpp"
#include <algorithm>
#include <map>
#include <unordered_map>

std::chrono::microseconds insercaoVector(int size, std::vector<double> numbers, std::vector<double> *vector);
std::chrono::microseconds searchVector(std::vector<double> numbers, std::vector<double> vector, std::vector<double> *remover);
std::chrono::microseconds remocaoVector(std::vector<double> numbers, std::vector<double> *vector);

std::chrono::microseconds insercaoMap(int size, std::vector<double> numbers, std::map<double,Record> *map);
std::chrono::microseconds searchMap(std::vector<double> numbers, std::map<double,Record> map, std::vector<double> *remover);
std::chrono::microseconds remocaoMap(std::vector<double> numbers, std::map<double,Record> *map);

std::chrono::microseconds insercaoUnorderedMap(int size, std::vector<double> numbers, std::unordered_map<double,Record> *unomap);
std::chrono::microseconds searchUnorderedMap(std::vector<double> numbers, std::unordered_map<double,Record> unomap, std::vector<double> *remover);
std::chrono::microseconds remocaoUnorderedMap(std::vector<double> numbers, std::unordered_map<double,Record> *unomap);

#endif