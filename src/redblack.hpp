#ifndef REDBLACK_HPP
#define REDBLACK_HPP

#include "avl.hpp"

struct RB{
	Record reg;
	RB *esq, *dir;
	RB *pai; //específico para rubro negra
	bool cor;  //específico para rubro negra (FALSE = VERMELHOR, TRUE = PRETO)
};

RB* CreateRB();
bool TVazia(RB **t);

void pesquisaRB(RB **t, RB **aux, Record r);
double isInRB(RB *t, Record r);

void rotacaoSimplesEsquerdaRB(RB **raiz, RB *child);
void rotacaoSimplesDireitaRB(RB **raiz, RB *child);

void insertFixUpRB(RB **raiz, RB *child);
void insertRB(RB **t, RB **pai, RB **raiz, Record r);

RB* minimumRB(RB *t);
void transplantRB(RB **raiz, RB **u, RB **v);
void deleteFixUpRB(RB **raiz, RB *x);
void deleteRB(RB **raiz, RB *z);
void removeRB(RB **t, RB **raiz, Record r);

void preordemRB(RB *t);
void centralRB(RB *t);
void posordemRB(RB *t);
void widthPathRB(RB *t);

std::chrono::microseconds insercaoRB(int size, std::vector<double> numbers, RB **t);
std::chrono::microseconds searchRB(std::vector<double> numbers, RB **t, std::vector<double> *remover);
std::chrono::microseconds remocaoRB(std::vector<double> numbers, RB **t);

#endif