#include "others.hpp"


std::chrono::microseconds insercaoVector(int size, std::vector<double> numbers, std::vector<double> *vector) {
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) {
        vector->push_back(numbers[i]);
    }
    std::sort(vector->begin(), vector->end());
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::chrono::microseconds searchVector(std::vector<double> numbers, std::vector<double> vector, std::vector<double> *remover) {
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(double x:numbers) {
        if (std::binary_search(vector.begin(), vector.end(), x)) {
            std::cout << std::setprecision(12) << x << std::endl;
            remover->push_back(x);
        }
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::chrono::microseconds remocaoVector(std::vector<double> numbers, std::vector<double> *vector) {
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(double x:numbers) {
        auto iterator= find(vector->begin(), vector->end(), x);
        if(iterator != vector->end()) {
            vector->erase(iterator);
        }
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::chrono::microseconds insercaoMap(int size, std::vector<double> numbers, std::map<double,Record> *map) {
    Record r;
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) {
        r.key = numbers[i];
        map->insert(std::pair<double, Record>(r.key, r));
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::chrono::microseconds searchMap(std::vector<double> numbers, std::map<double,Record> map, std::vector<double> *remover) {
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(double x:numbers) {
        auto it = map.find(x);
        remover->push_back(it->first);
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::chrono::microseconds remocaoMap(std::vector<double> numbers, std::map<double,Record> *map) {
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(double x:numbers) {
        map->erase(x);
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::chrono::microseconds insercaoUnorderedMap(int size, std::vector<double> numbers, std::unordered_map<double,Record> *unomap) {
    Record r;
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) {
        r.key = numbers[i];
        (*unomap)[r.key] = r;
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::chrono::microseconds searchUnorderedMap(std::vector<double> numbers, std::unordered_map<double,Record> unomap, std::vector<double> *remover) {
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(double x:numbers) {
        if(unomap.find(x) != unomap.end()) {
            remover->push_back(x);
        }
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::chrono::microseconds remocaoUnorderedMap(std::vector<double> numbers, std::unordered_map<double,Record> *unomap) {
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(double x:numbers) {
        unomap->erase(x);
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}