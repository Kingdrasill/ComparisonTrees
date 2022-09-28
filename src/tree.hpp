#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <random>
#include <queue>

typedef struct Record Record;
typedef struct Tree Tree;

struct Record{
	double key;
};

struct Tree{
	Record reg;
	Tree *esq, *dir;
	int weight; // específico para AVL
	Tree *pai; //específico para rubro negra
	bool cor;  //específico para rubro negra (FALSE = VERMELHOR, TRUE = PRETO)
};

Tree* CreateTree();
bool TVazia(Tree **t);
void insertTree(Tree **t, Record r);
void pesquisa(Tree **t, Tree **aux, Record r);
int isInTree(Tree *t, Record r);

void removeTree(Tree **t, Record r);
void antecessor(Tree **t, Tree *aux);

void preordem(Tree *t);
void central(Tree *t);
void posordem(Tree *t);
void widthPath(Tree *t);

#endif