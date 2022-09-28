#ifndef REDBLACK_HPP
#define REDBLACK_HPP

#include "avl.hpp"

void rotacaoSimplesEsquerdaRB(Tree **raiz, Tree *child);
void rotacaoSimplesDireitaRB(Tree **raiz, Tree *child);

void insertFixUpRB(Tree **raiz, Tree *child);
void insertTreeRB(Tree **t, Tree **pai, Tree **raiz, Record r);

void preordemRB(Tree *t);
void centralRB(Tree *t);
void posordemRB(Tree *t);

#endif