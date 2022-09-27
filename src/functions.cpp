#include "functions.hpp"

void createFile() {
    const int min = 10000;
    const int max = 100000;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min,max);

    std::fstream file;
    std::string nome = "teste.txt";

    /* std::cout << "Qual o nome do arquivo: " << std::endl;
    std::cin >> nome; */

    file.open(nome, std::ios::out);
    if(file.is_open()) {
        for(int i=0; i<50000; i++) {
            file << std::setprecision(11) << dis(gen) << "\t";
        }
    } else {
        std::cout << "Nao foi posssivel abrir o arquivo " << nome << "!" << std::endl;
    }
    file.close();
}

void readFile() {
    std::fstream file;
    std::string nome = "teste.txt";
    Tree *raiz;
    Record r;
    TVazia(&raiz);

    /* std::cout << "Qual o nome do arquivo: " << std::endl;
    std::cin >> nome; */

    file.open(nome, std::ios::in);
    if(file.is_open()) {
        for(int i=0; i<50000; i++) {
            file >> r.key;
            insertTree(&raiz, r);
        }
    } else {
        std::cout << "Nao foi posssivel abrir o arquivo " << nome << "!" << std::endl;
    }
    file.close();

    central(raiz);
}