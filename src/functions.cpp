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

void readFiles(std::vector<Times> *tempos) {
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

    Times t;
    
    for(int i=0; i<4; i++) {
        int size = base * pow(10, i);
        static std::vector<double> remover;

        Tree *tree = CreateTree();
        t.binaryTree.insertion.push_back(insercaoTree(size, insertion, &tree));
        t.binaryTree.search.push_back(searchTree(search, &tree, &remover));
        t.binaryTree.remove.push_back(remocaoTree(remover, &tree));
        delete tree;
        remover.clear();

        AVL *avl = CreateAVL();
        t.avlTree.insertion.push_back(insercaoAVL(size, insertion, &avl));
        t.avlTree.search.push_back(searchAVL(search, &avl, &remover));
        t.avlTree.remove.push_back(remocaoAVL(remover, &avl));
        delete avl;
        remover.clear();

        RB *rb = CreateRB();
        t.redblackTree.insertion.push_back(insercaoRB(size, insertion, &rb));
        t.redblackTree.search.push_back(searchRB(search, &rb, &remover));
        t.redblackTree.remove.push_back(remocaoRB(remover, &rb));
        delete rb;
        remover.clear();

        std::map<double, Record> map;
        t.mapTimes.insertion.push_back(insercaoMap(size, insertion, &map));
        t.mapTimes.search.push_back(searchMap(search, map, &remover));
        t.mapTimes.remove.push_back(remocaoMap(remover, &map));
        map.clear();
        remover.clear();

        std::unordered_map<double, Record> unomap;
        t.unomapTimes.insertion.push_back(insercaoUnorderedMap(size, insertion, &unomap));
        t.unomapTimes.search.push_back(searchUnorderedMap(search, unomap, &remover));
        t.unomapTimes.remove.push_back(remocaoUnorderedMap(remover, &unomap));
        unomap.clear();
        remover.clear();

        std::vector<double> vetor;
        t.vetorTimes.insertion.push_back(insercaoVector(size, insertion, &vetor));
        t.vetorTimes.search.push_back(searchVector(search, vetor, &remover));
        t.vetorTimes.remove.push_back(remocaoVector(remover, &vetor));
        vetor.clear();
        remover.clear();
    }

    tempos->push_back(t);

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

void createTimeFile(std::vector<Times> tempos, int n) {
    std::string name = "tempos.txt";
    std::fstream file;

    file.open(name, std::ios::out);
    if (file.is_open()) {
        file << "Tempo da insercao médio em milisegundos para cada estrutura com tamanhos:\t500\t|\t5000\t|\t50000\t|\t500000\t" << std::endl;
        fillFileWithAverageTime(tempos, n, 1, &file);
        file << "\nTempo da busca médio em milisegundos para cada estrutura com tamanhos:\t500\t|\t5000\t|\t50000\t|\t500000\t" << std::endl;
        fillFileWithAverageTime(tempos, n, 2, &file);
        file << "\nTempo da remocao médio em milisegundos para cada estrutura com tamanhos:\t500\t|\t5000\t|\t50000\t|\t500000\t" << std::endl;
        fillFileWithAverageTime(tempos, n, 3, &file);
        file << std::endl;
        for(int i=0; i<n; i++) {
            file << "Tempos Teste " << (i+1) << "\n" << std::endl;
            file << "Tempo da insercao em milisegundos para cada estrutura com tamanhos:\t500\t|\t5000\t|\t50000\t|\t500000\t" << std::endl;
            fillFileWithTime(tempos[i], 1, &file);
            file << "\nTempo da busca em milisegundos para cada estrutura com tamanhos:\t500\t|\t5000\t|\t50000\t|\t500000\t" << std::endl;
            fillFileWithTime(tempos[i], 2, &file);
            file << "\nTempo da remocao em milisegundos para cada estrutura com tamanhos:\t500\t|\t5000\t|\t50000\t|\t500000\t" << std::endl;
            fillFileWithTime(tempos[i], 3, &file);
            file << std::endl;
        }
    } else {
        std::cout << "Nao foi posssivel abrir o arquivo " << name << "!" << std::endl;
    }
    file.close();
}

void fillFileWithTime(Times tempos, int tipo, std::fstream *file) {
    double t500, t5000, t50000, t500000;

    t500 = timeToMiliseconds(tempos, 1, tipo, 1);
    t5000 = timeToMiliseconds(tempos, 1, tipo, 2);
    t50000 = timeToMiliseconds(tempos, 1, tipo, 3);
    t500000 = timeToMiliseconds(tempos, 1, tipo, 4);
    *file << "Arvore Binaria:\t" << t500 << "\t|\t" << t5000 << "\t|\t" << t50000 << "\t|\t" << t500000 << "\t" << std::endl;

    t500 = timeToMiliseconds(tempos, 2, tipo, 1);
    t5000 = timeToMiliseconds(tempos, 2, tipo, 2);
    t50000 = timeToMiliseconds(tempos, 2, tipo, 3);
    t500000 = timeToMiliseconds(tempos, 2, tipo, 4);

    *file << "Arvore AVL:\t" << t500 << "\t|\t" << t5000 << "\t|\t" << t50000 << "\t|\t" << t500000 << "\t" << std::endl;

    t500 = timeToMiliseconds(tempos, 3, tipo, 1);
    t5000 = timeToMiliseconds(tempos, 3, tipo, 2);
    t50000 = timeToMiliseconds(tempos, 3, tipo, 3);
    t500000 = timeToMiliseconds(tempos, 3, tipo, 4);

    *file << "Arvore RedBlack:\t" << t500 << "\t|\t" << t5000 << "\t|\t" << t50000 << "\t|\t" << t500000 << "\t" << std::endl;

    t500 = timeToMiliseconds(tempos, 4, tipo, 1);
    t5000 = timeToMiliseconds(tempos, 4, tipo, 2);
    t50000 = timeToMiliseconds(tempos, 4, tipo, 3);
    t500000 = timeToMiliseconds(tempos, 4, tipo, 4);

    *file << "Map:\t" << t500 << "\t|\t" << t5000 << "\t|\t" << t50000 << "\t|\t" << t500000 << "\t" << std::endl;

    t500 = timeToMiliseconds(tempos, 5, tipo, 1);
    t5000 = timeToMiliseconds(tempos, 5, tipo, 2);
    t50000 = timeToMiliseconds(tempos, 5, tipo, 3);
    t500000 = timeToMiliseconds(tempos, 5, tipo, 4);

    *file << "Unordered Map:\t" << t500 << "\t|\t" << t5000 << "\t|\t" << t50000 << "\t|\t" << t500000 << "\t" << std::endl;

    t500 = timeToMiliseconds(tempos, 6, tipo, 1);
    t5000 = timeToMiliseconds(tempos, 6, tipo, 2);
    t50000 = timeToMiliseconds(tempos, 6, tipo, 3);
    t500000 = timeToMiliseconds(tempos, 6, tipo, 4);

    *file << "Vetor:\t" << t500 << "\t|\t" << t5000 << "\t|\t" << t50000 << "\t|\t" << t500000 << "\t" << std::endl;
}

void fillFileWithAverageTime(std::vector<Times> tempos, int n, int tipo, std::fstream *file) {
    double t500, t5000, t50000, t500000;

    t500 = averageTimeToMiliseconds(tempos, n, 1, tipo, 1);
    t5000 = averageTimeToMiliseconds(tempos, n, 1, tipo, 2);
    t50000 = averageTimeToMiliseconds(tempos, n, 1, tipo, 3);
    t500000 = averageTimeToMiliseconds(tempos, n, 1, tipo, 4);

    *file << "Arvore Binaria:\t" << t500 << "\t|\t" << t5000 << "\t|\t" << t50000 << "\t|\t" << t500000 << "\t" << std::endl;

    t500 = averageTimeToMiliseconds(tempos, n, 2, tipo, 1);
    t5000 = averageTimeToMiliseconds(tempos, n, 2, tipo, 2);
    t50000 = averageTimeToMiliseconds(tempos, n, 2, tipo, 3);
    t500000 = averageTimeToMiliseconds(tempos, n, 2, tipo, 4);

    *file << "Arvore AVL:\t" << t500 << "\t|\t" << t5000 << "\t|\t" << t50000 << "\t|\t" << t500000 << "\t" << std::endl;

    t500 = averageTimeToMiliseconds(tempos, n, 3, tipo, 1);
    t5000 = averageTimeToMiliseconds(tempos, n, 3, tipo, 2);
    t50000 = averageTimeToMiliseconds(tempos, n, 3, tipo, 3);
    t500000 = averageTimeToMiliseconds(tempos, n, 3, tipo, 4);

    *file << "Arvore RedBlack:\t" << t500 << "\t|\t" << t5000 << "\t|\t" << t50000 << "\t|\t" << t500000 << "\t" << std::endl;

    t500 = averageTimeToMiliseconds(tempos, n, 4, tipo, 1);
    t5000 = averageTimeToMiliseconds(tempos, n, 4, tipo, 2);
    t50000 = averageTimeToMiliseconds(tempos, n, 4, tipo, 3);
    t500000 = averageTimeToMiliseconds(tempos, n, 4, tipo, 4);

    *file << "Map:\t" << t500 << "\t|\t" << t5000 << "\t|\t" << t50000 << "\t|\t" << t500000 << "\t" << std::endl;

    t500 = averageTimeToMiliseconds(tempos, n, 5, tipo, 1);
    t5000 = averageTimeToMiliseconds(tempos, n, 5, tipo, 2);
    t50000 = averageTimeToMiliseconds(tempos, n, 5, tipo, 3);
    t500000 = averageTimeToMiliseconds(tempos, n, 5, tipo, 4);

    *file << "Unordered Map:\t" << t500 << "\t|\t" << t5000 << "\t|\t" << t50000 << "\t|\t" << t500000 << "\t" << std::endl;

    t500 = averageTimeToMiliseconds(tempos, n, 6, tipo, 1);
    t5000 = averageTimeToMiliseconds(tempos, n, 6, tipo, 2);
    t50000 = averageTimeToMiliseconds(tempos, n, 6, tipo, 3);
    t500000 = averageTimeToMiliseconds(tempos, n, 6, tipo, 4);

    *file << "Vetor:\t" << t500 << "\t|\t" << t5000 << "\t|\t" << t50000 << "\t|\t" << t500000 << "\t" << std::endl;
}


double timeToMiliseconds(Times tempos, int estrutura, int tipo, int size) {
    double time = 0;
    switch(estrutura) {
        case 1:
            switch(tipo) {
                case 1:
                    switch(size) {
                        case 1:
                            time = tempos.binaryTree.insertion[0].count();
                            break;
                        case 2:
                            time = tempos.binaryTree.insertion[1].count();
                            break;
                        case 3:
                            time = tempos.binaryTree.insertion[2].count();
                            break;
                        case 4:
                            time = tempos.binaryTree.insertion[3].count();
                            break;
                    }
                    break;
                case 2:
                    switch(size) {
                        case 1:
                            time = tempos.binaryTree.search[0].count();
                            break;
                        case 2:
                            time = tempos.binaryTree.search[1].count();
                            break;
                        case 3:
                            time = tempos.binaryTree.search[2].count();
                            break;
                        case 4:
                            time = tempos.binaryTree.search[3].count();
                            break;
                    }
                    break;
                case 3:
                    switch(size) {
                        case 1:
                            time = tempos.binaryTree.remove[0].count();
                            break;
                        case 2:
                            time = tempos.binaryTree.remove[1].count();
                            break;
                        case 3:
                            time = tempos.binaryTree.remove[2].count();
                            break;
                        case 4:
                            time = tempos.binaryTree.remove[3].count();
                            break;
                    }
                    break;
            }
            break;
        case 2:
            switch(tipo) {
                case 1:
                    switch(size) {
                        case 1:
                            time = tempos.avlTree.insertion[0].count();
                            break;
                        case 2:
                            time = tempos.avlTree.insertion[1].count();
                            break;
                        case 3:
                            time = tempos.avlTree.insertion[2].count();
                            break;
                        case 4:
                            time = tempos.avlTree.insertion[3].count();
                            break;
                    }
                    break;
                case 2:
                    switch(size) {
                        case 1:
                            time = tempos.avlTree.search[0].count();
                            break;
                        case 2:
                            time = tempos.avlTree.search[1].count();
                            break;
                        case 3:
                            time = tempos.avlTree.search[2].count();
                            break;
                        case 4:
                            time = tempos.avlTree.search[3].count();
                            break;
                    }
                    break;
                case 3:
                    switch(size) {
                        case 1:
                            time = tempos.avlTree.remove[0].count();
                            break;
                        case 2:
                            time = tempos.avlTree.remove[1].count();
                            break;
                        case 3:
                            time = tempos.avlTree.remove[2].count();
                            break;
                        case 4:
                            time = tempos.avlTree.remove[3].count();
                            break;
                    }
                    break;
            }
            break;
        case 3:
            switch(tipo) {
                case 1:
                    switch(size) {
                        case 1:
                            time = tempos.redblackTree.insertion[0].count();
                            break;
                        case 2:
                            time = tempos.redblackTree.insertion[1].count();
                            break;
                        case 3:
                            time = tempos.redblackTree.insertion[2].count();
                            break;
                        case 4:
                            time = tempos.redblackTree.insertion[3].count();
                            break;
                    }
                    break;
                case 2:
                    switch(size) {
                        case 1:
                            time = tempos.redblackTree.search[0].count();
                            break;
                        case 2:
                            time = tempos.redblackTree.search[1].count();
                            break;
                        case 3:
                            time = tempos.redblackTree.search[2].count();
                            break;
                        case 4:
                            time = tempos.redblackTree.search[3].count();
                            break;
                    }
                    break;
                case 3:
                    switch(size) {
                        case 1:
                            time = tempos.redblackTree.remove[0].count();
                            break;
                        case 2:
                            time = tempos.redblackTree.remove[1].count();
                            break;
                        case 3:
                            time = tempos.redblackTree.remove[2].count();
                            break;
                        case 4:
                            time = tempos.redblackTree.remove[3].count();
                            break;
                    }
                    break;
            }
            break;
        case 4:
            switch(tipo) {
                case 1:
                    switch(size) {
                        case 1:
                            time = tempos.mapTimes.insertion[0].count();
                            break;
                        case 2:
                            time = tempos.mapTimes.insertion[1].count();
                            break;
                        case 3:
                            time = tempos.mapTimes.insertion[2].count();
                            break;
                        case 4:
                            time = tempos.mapTimes.insertion[3].count();
                            break;
                    }
                    break;
                case 2:
                    switch(size) {
                        case 1:
                            time = tempos.mapTimes.search[0].count();
                            break;
                        case 2:
                            time = tempos.mapTimes.search[1].count();
                            break;
                        case 3:
                            time = tempos.mapTimes.search[2].count();
                            break;
                        case 4:
                            time = tempos.mapTimes.search[3].count();
                            break;
                    }
                    break;
                case 3:
                    switch(size) {
                        case 1:
                            time = tempos.mapTimes.remove[0].count();
                            break;
                        case 2:
                            time = tempos.mapTimes.remove[1].count();
                            break;
                        case 3:
                            time = tempos.mapTimes.remove[2].count();
                            break;
                        case 4:
                            time = tempos.mapTimes.remove[3].count();
                            break;
                    }
                    break;
            }
            break;
        case 5:
            switch(tipo) {
                case 1:
                    switch(size) {
                        case 1:
                            time = tempos.unomapTimes.insertion[0].count();
                            break;
                        case 2:
                            time = tempos.unomapTimes.insertion[1].count();
                            break;
                        case 3:
                            time = tempos.unomapTimes.insertion[2].count();
                            break;
                        case 4:
                            time = tempos.unomapTimes.insertion[3].count();
                            break;
                    }
                    break;
                case 2:
                    switch(size) {
                        case 1:
                            time = tempos.unomapTimes.search[0].count();
                            break;
                        case 2:
                            time = tempos.unomapTimes.search[1].count();
                            break;
                        case 3:
                            time = tempos.unomapTimes.search[2].count();
                            break;
                        case 4:
                            time = tempos.unomapTimes.search[3].count();
                            break;
                    }
                    break;
                case 3:
                    switch(size) {
                        case 1:
                            time = tempos.unomapTimes.remove[0].count();
                            break;
                        case 2:
                            time = tempos.unomapTimes.remove[1].count();
                            break;
                        case 3:
                            time = tempos.unomapTimes.remove[2].count();
                            break;
                        case 4:
                            time = tempos.unomapTimes.remove[3].count();
                            break;
                    }
                    break;
            }
            break;
        case 6:
            switch(tipo) {
                case 1:
                    switch(size) {
                        case 1:
                            time = tempos.vetorTimes.insertion[0].count();
                            break;
                        case 2:
                            time = tempos.vetorTimes.insertion[1].count();
                            break;
                        case 3:
                            time = tempos.vetorTimes.insertion[2].count();
                            break;
                        case 4:
                            time = tempos.vetorTimes.insertion[3].count();
                            break;
                    }
                    break;
                case 2:
                    switch(size) {
                        case 1:
                            time = tempos.vetorTimes.search[0].count();
                            break;
                        case 2:
                            time = tempos.vetorTimes.search[1].count();
                            break;
                        case 3:
                            time = tempos.vetorTimes.search[2].count();
                            break;
                        case 4:
                            time = tempos.vetorTimes.search[3].count();
                            break;
                    }
                    break;
                case 3:
                    switch(size) {
                        case 1:
                            time = tempos.vetorTimes.remove[0].count();
                            break;
                        case 2:
                            time = tempos.vetorTimes.remove[1].count();
                            break;
                        case 3:
                            time = tempos.vetorTimes.remove[2].count();
                            break;
                        case 4:
                            time = tempos.vetorTimes.remove[3].count();
                            break;
                    }
                    break;
            }
            break;
    }
    time = time/1000;
    return time;
}

double averageTimeToMiliseconds(std::vector<Times> tempos, int n, int estrutura, int tipo, int size) {
    double time = 0;
    switch(estrutura) {
        case 1:
            switch(tipo) {
                case 1:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.binaryTree.insertion[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.binaryTree.insertion[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.binaryTree.insertion[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.binaryTree.insertion[3].count();
                            }
                            break;
                    }
                    break;
                case 2:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.binaryTree.search[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.binaryTree.search[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.binaryTree.search[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.binaryTree.search[3].count();
                            }
                            break;
                    }
                    break;
                case 3:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.binaryTree.remove[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.binaryTree.remove[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.binaryTree.remove[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.binaryTree.remove[3].count();
                            }
                            break;
                    }
                    break;
            }
            break;
        case 2:
            switch(tipo) {
                case 1:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.avlTree.insertion[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.avlTree.insertion[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.avlTree.insertion[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.avlTree.insertion[3].count();
                            }
                            break;
                    }
                    break;
                case 2:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.avlTree.search[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.avlTree.search[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.avlTree.search[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.avlTree.search[3].count();
                            }
                            break;
                    }
                    break;
                case 3:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.avlTree.remove[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.avlTree.remove[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.avlTree.remove[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.avlTree.remove[3].count();
                            }
                            break;
                    }
                    break;
            }
            break;
        case 3:
            switch(tipo) {
                case 1:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.redblackTree.insertion[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.redblackTree.insertion[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.redblackTree.insertion[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.redblackTree.insertion[3].count();
                            }
                            break;
                    }
                    break;
                case 2:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.redblackTree.search[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.redblackTree.search[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.redblackTree.search[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.redblackTree.search[3].count();
                            }
                            break;
                    }
                    break;
                case 3:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.redblackTree.remove[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.redblackTree.remove[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.redblackTree.remove[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.redblackTree.remove[3].count();
                            }
                            break;
                    }
                    break;
            }
            break;
        case 4:
            switch(tipo) {
                case 1:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.mapTimes.insertion[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.mapTimes.insertion[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.mapTimes.insertion[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.mapTimes.insertion[3].count();
                            }
                            break;
                    }
                    break;
                case 2:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.mapTimes.search[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.mapTimes.search[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.mapTimes.search[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.mapTimes.search[3].count();
                            }
                            break;
                    }
                    break;
                case 3:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.mapTimes.remove[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.mapTimes.remove[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.mapTimes.remove[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.mapTimes.remove[3].count();
                            }
                            break;
                    }
                    break;
            }
            break;
        case 5:
            switch(tipo) {
                case 1:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.unomapTimes.insertion[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.unomapTimes.insertion[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.unomapTimes.insertion[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.unomapTimes.insertion[3].count();
                            }
                            break;
                    }
                    break;
                case 2:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.unomapTimes.search[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.unomapTimes.search[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.unomapTimes.search[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.unomapTimes.search[3].count();
                            }
                            break;
                    }
                    break;
                case 3:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.unomapTimes.remove[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.unomapTimes.remove[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.unomapTimes.remove[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.unomapTimes.remove[3].count();
                            }
                            break;
                    }
                    break;
            }
            break;
        case 6:
            switch(tipo) {
                case 1:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.vetorTimes.insertion[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.vetorTimes.insertion[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.vetorTimes.insertion[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.vetorTimes.insertion[3].count();
                            }
                            break;
                    }
                    break;
                case 2:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.vetorTimes.search[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.vetorTimes.search[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.vetorTimes.search[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.vetorTimes.search[3].count();
                            }
                            break;
                    }
                    break;
                case 3:
                    switch(size) {
                        case 1:
                            for(Times x:tempos) {
                                time += x.vetorTimes.remove[0].count();
                            }
                            break;
                        case 2:
                            for(Times x:tempos) {
                                time += x.vetorTimes.remove[1].count();
                            }
                            break;
                        case 3:
                            for(Times x:tempos) {
                                time += x.vetorTimes.remove[2].count();
                                }
                            break;
                        case 4:
                            for(Times x:tempos) {
                                time += x.vetorTimes.remove[3].count();
                            }
                            break;
                    }
                    break;
            }
            break;
    }
    time = time / n;
    time = time / 1000;
    return time;
}