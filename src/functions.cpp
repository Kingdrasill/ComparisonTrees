#include "functions.hpp"

void createFiles() {
    const int min = 0;
    const int max = 1000000;
    
    std::vector<double> numbers;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min,max);

    std::fstream file;
    std::string insercao = "insercao.txt";
    std::string pesquisa = "pesquisa.txt";

    file.open(insercao, std::ios::out);
    if(file.is_open()) {
        for(int i=0; i<500000; i++) {
            double n = dis(gen);
            numbers.push_back(n);
            file << std::setprecision(12) << n << "\t";
        }
    } else {
        std::cout << "Nao foi posssivel abrir o arquivo " << insercao << "!" << std::endl;
    }
    file.close();
    
    std::uniform_real_distribution<double> dis2(min,-max);
    std::uniform_real_distribution<double> dis3(0,1);
    std::random_device rt; 
    std::default_random_engine rng(rt());

    file.open(pesquisa, std::ios::out);
    if(file.is_open()) {
        for(int i=0; i<10000; i++) {
            double d = dis3(gen);
            if(d <= 0.75) {
                double n = numbers.back();
                numbers.pop_back();
                std::shuffle(std::begin(numbers), std::end(numbers), rng);
                file << std::setprecision(12) << n << "\t";
            } else {
                double n = dis2(gen);
                file << std::setprecision(12) << n << "\t";
            }
        }
    } else {
        std::cout << "Nao foi posssivel abrir o arquivo " << pesquisa << "!" << std::endl;
    }
    file.close();
}

void readFiles() {
    std::random_device rd; 
    std::default_random_engine rng(rd());

    std::fstream file;
    std::string insercao = "insercao.txt", pesquisa = "pesquisa.txt";
    std::vector<double> insertion, search;
    int base = 500;

    double d;
    file.open(insercao, std::ios::in);
    if(file.is_open()) {
        for(int i=0; i<500000; i++) {
            file >> d;
            insertion.push_back(d);
        }
    } else {
        std::cout << "Nao foi posssivel abrir o arquivo " << insercao << "!" << std::endl;
    }
    file.close();
    file.open(pesquisa, std::ios::in);
    if(file.is_open()) {
        for(int i=0; i<10000; i++) {
            file >> d;
            search.push_back(d);
        }
    } else {
        std::cout << "Nao foi posssivel abrir o arquivo " << pesquisa << "!" << std::endl;
    }
    file.close();

    Times binaryTree, avlTree, redblackTree, vetorTimes, mapTimes, unomapTimes;
    
    for(int i=0; i<4; i++) {
        int size = base * pow(10, i);
        static std::vector<double> remover;

        Tree *tree = CreateTree();
        binaryTree.insertion.push_back(insercaoTree(size, insertion, &tree));
        binaryTree.search.push_back(searchTree(search, &tree, &remover));
        binaryTree.remove.push_back(remocaoTree(remover, &tree));
        delete tree;
        remover.clear();

        AVL *avl = CreateAVL();
        avlTree.insertion.push_back(insercaoAVL(size, insertion, &avl));
        avlTree.search.push_back(searchAVL(search, &avl, &remover));
        avlTree.remove.push_back(remocaoAVL(remover, &avl));
        delete avl;
        remover.clear();

        RB *rb = CreateRB();
        redblackTree.insertion.push_back(insercaoRB(size, insertion, &rb));
        redblackTree.search.push_back(searchRB(search, &rb, &remover));
        redblackTree.remove.push_back(remocaoRB(remover, &rb));
        delete rb;
        remover.clear();

        static std::map<double, Record> map;
        mapTimes.insertion.push_back(insercaoMap(size, insertion, &map));
        mapTimes.search.push_back(searchMap(search, map, &remover));
        mapTimes.remove.push_back(remocaoMap(remover, &map));
        map.clear();
        remover.clear();

        static std::unordered_map<double, Record> unomap;
        unomapTimes.insertion.push_back(insercaoUnorderedMap(size, insertion, &unomap));
        unomapTimes.search.push_back(searchUnorderedMap(search, unomap, &remover));
        unomapTimes.remove.push_back(remocaoUnorderedMap(remover, &unomap));
        unomap.clear();
        remover.clear();

        static std::vector<double> vetor;
        vetorTimes.insertion.push_back(insercaoVector(size, insertion, &vetor));
        vetorTimes.search.push_back(searchVector(search, vetor, &remover));
        vetorTimes.remove.push_back(remocaoVector(remover, &vetor));
        vetor.clear();
        remover.clear();
    }

    printf("\n\n\n");
    std::cout << "Descricao : Binary Tree | AVL Tree | RedBlackTree | Map | Unordeder_Map  | Vetor" << std::endl;
    for(int i=0; i<4; i++) {
        int size = base * pow(10, i);
        std::cout << "Tempo em microsegundos para insercao de " << size << " numeros: " 
                    << binaryTree.insertion[i].count() << " | "  
                    << avlTree.insertion[i].count() << " | "  
                    << redblackTree.insertion[i].count() << " | "
                    << mapTimes.insertion[i].count() << " | "
                    << unomapTimes.insertion[i].count() << " | "
                    << vetorTimes.insertion[i].count() << std::endl;
        std::cout << "Tempo em microsegundos para pesquisa de 10000 numeros com " << size << " numeros: " 
                    << binaryTree.search[i].count() << " | "  
                    << avlTree.search[i].count() << " | "  
                    << redblackTree.search[i].count() << " | "  
                    << mapTimes.search[i].count() << " | "  
                    << unomapTimes.search[i].count() << " | "  
                    << vetorTimes.search[i].count() << std::endl;
        std::cout << "Tempo em microsegundos para remocao dos numeros encontrados na pesquisa com " << size << " numeros: " 
                    << binaryTree.remove[i].count() << " | "  
                    << avlTree.remove[i].count() << " | "  
                    << redblackTree.remove[i].count() << " | "  
                    << mapTimes.remove[i].count() << " | "  
                    << unomapTimes.remove[i].count() << " | "  
                    << vetorTimes.remove[i].count() << std::endl;

        printf("\n");
    }

    std::shuffle(std::begin(insertion), std::end(insertion), rng);
    std::shuffle(std::begin(search), std::end(search), rng);

    file.open(insercao, std::ios::out);
    if(file.is_open()) {
        for(int i=0; i<500000; i++) {
            file << std::setprecision(12) << insertion[i] << "\t";
        }
    } else {
        std::cout << "Nao foi posssivel abrir o arquivo " << insercao << "!" << std::endl;
    }
    file.close();
    insertion.clear();
    file.open(pesquisa, std::ios::out);
    if(file.is_open()) {
        for(int i=0; i<10000; i++) {
            file << std::setprecision(12) << search[i] << "\t";
        }
    } else {
        std::cout << "Nao foi posssivel abrir o arquivo " << pesquisa << "!" << std::endl;
    }
    file.close();
    search.clear();
}