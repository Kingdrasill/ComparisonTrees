#ifndef AVL_HPP
#define AVL_HPP

#include "tree.hpp"

struct AVL{
	Record reg;
	AVL *esq, *dir;
	int weight;
};

AVL* CreateAVL();
bool TVazia(AVL **t);

void insertAVL(AVL **t, Record r);
void pesquisaAVL(AVL **t, AVL **aux, Record r);
double isInAVL(AVL *t, Record r);

//muda o remove devido a necessidade de ponteiro para sub-árvore desbalanceada
void removeAVL(AVL **t, AVL **f, Record r);
void antecessorAVL(AVL **t, AVL *aux);
void rebalanceAVL(AVL **t);

void preordemAVL(AVL *t);
void centralAVL(AVL *t);
void posordemAVL(AVL *t);

int getWeight(AVL **t);
int getMaxWeight(int left, int right);

void rotacaoSimplesDireitaAVL(AVL **t);
void rotacaoSimplesEsquerdaAVL(AVL **t);
void rotacaoDuplaDireitaAVL(AVL **t);
void rotacaoDuplaEsquerdaAVL(AVL **t);
void widthPathAVL(AVL *t);

std::chrono::microseconds insercaoAVL(int size, std::vector<double> numbers, AVL **t);
std::chrono::microseconds searchAVL(std::vector<double> numbers, AVL **t, std::vector<double> *remover);
std::chrono::microseconds remocaoAVL(std::vector<double> numbers, AVL **t);


#endif