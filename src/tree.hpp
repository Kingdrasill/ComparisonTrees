#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <iomanip>

typedef struct Record Record;
typedef struct Tree Tree;

struct Record{
	double key;
};

struct Tree{
	Record reg;
	Tree *esq, *dir;
};

Tree* CreateTree();
bool TVazia(Tree **t);
void insertTree(Tree **t, Record r);
void pesquisa(Tree **t, Tree **aux, Record r);
double isInTree(Tree *t, Record r);

void removeTree(Tree **t, Record r);
void antecessor(Tree **t, Tree *aux);

void preordem(Tree *t);
void central(Tree *t);
void posordem(Tree *t);
void widthPath(Tree *t);

std::chrono::microseconds insercaoTree(int size, std::vector<double> numbers, Tree **t);
std::chrono::microseconds searchTree(std::vector<double> numbers, Tree **t, std::vector<double> *remover);
std::chrono::microseconds remocaoTree(std::vector<double> numbers, Tree **t);

#endif