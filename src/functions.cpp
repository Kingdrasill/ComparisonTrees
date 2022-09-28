#include "functions.hpp"

void createFile() {
    const int min = 0;
    const int max = 1000000;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min,max);

    std::fstream file;
    std::string nome = "teste.txt";

    /* std::cout << "Qual o nome do arquivo: " << std::endl;
    std::cin >> nome; */

    file.open(nome, std::ios::out);
    if(file.is_open()) {
        for(int i=0; i<500000; i++) {
            file << std::setprecision(12) << dis(gen) << "\t";
        }
    } else {
        std::cout << "Nao foi posssivel abrir o arquivo " << nome << "!" << std::endl;
    }
    file.close();
}

void readFile() {
    std::fstream file;
    std::string nome = "teste.txt";
    /* std::vector<double> list;
    double d; */
    Tree *raiz;
    Record r;
    TVazia(&raiz);

    /* std::cout << "Qual o nome do arquivo: " << std::endl;
    std::cin >> nome; */

    file.open(nome, std::ios::in);
    if(file.is_open()) {
        for(int i=0; i<500000; i++) {
            /* file >> d;
            list.push_back(d); */
            file >> r.key;
            insertTree(&raiz, r);
        }
    } else {
        std::cout << "Nao foi posssivel abrir o arquivo " << nome << "!" << std::endl;
    }
    file.close();

    /* std::sort(list.begin(), list.end());
    list.erase(std::unique(list.begin(), list.end()), list.end());

    for(double i: list)
        std::cout << std::setprecision(12) << i << std::endl;

    printf("\n%ld\n", list.size()); */

    widthPath(raiz);
}