#include "redblack.hpp"

void insertFixUpRB(Tree **raiz, Tree *child){
    Tree *tio;

    while((child != *raiz) && (child->pai->cor == false)){
        
        if(child->pai == child->pai->pai->esq){
            
            tio = child->pai->pai->dir;

            //caso 1:
            if((tio != NULL) && (tio->cor == false)){
                child->pai->cor = true;
                tio->cor = true;
                child->pai->pai->cor = false;
                child = child->pai->pai;
            
            }else{
            
                //caso 2
                if(child == child->pai->dir){
                    child = child->pai;
                    rotacaoSimplesEsquerdaRB(raiz, child);
                }
                
                //caso 3
                child->pai->cor = true;
                child->pai->pai->cor = false;
                rotacaoSimplesDireitaRB(raiz, child->pai->pai);
            }

        }else{
            
            tio = child->pai->pai->esq;
            
            //caso 1
            if((tio != NULL) && (tio->cor == false)){
                child->pai->cor = true;
                tio->cor = true;
                child->pai->pai->cor = false;
                child = child->pai->pai;
            
            }else{
            
                //caso 2
                if(child == child->pai->esq){
                    child = child->pai;
                    rotacaoSimplesDireitaRB(raiz, child);
                }

                //caso 3
                child->pai->cor = true;
                child->pai->pai->cor = false;
                rotacaoSimplesEsquerdaRB(raiz, child->pai->pai);      
            }

        }

    }

    (*raiz)->cor = true;
}


void insertTreeRB(Tree **t, Tree **pai, Tree **raiz, Record r){
    if(*t == NULL){
        *t = (Tree*)malloc(sizeof(Tree));
        (*t)->esq = NULL; 
        (*t)->dir = NULL; 
        (*t)->pai = pai!=t?*pai:NULL;
        (*t)->cor = false; //false: vermelho  true:preto
        (*t)->reg = r; 
        insertFixUpRB(raiz, *t);  
    } else { 
        if(r.key < (*t)->reg.key){
            insertTreeRB(&(*t)->esq, t, raiz, r);
            return;
        }
        
        if(r.key > (*t)->reg.key){
            insertTreeRB(&(*t)->dir, t, raiz, r);
            return;
        }
    }
}

void rotacaoSimplesEsquerdaRB(Tree **raiz, Tree *child){
    Tree *x, *y;

    x = child;
    y = child->dir;
    x->dir = y->esq;

    if(y->esq != NULL)
        y->esq->pai = x;

    y->pai = x->pai;
    
    if(x->pai == NULL)
        *raiz = y;

    else{

        if(x == x->pai->esq)
        x->pai->esq = y;

        else
        x->pai->dir = y;
    
    }

    y->esq = x;
    x->pai = y;
}

void rotacaoSimplesDireitaRB(Tree **raiz, Tree *child){
    Tree *x, *y;

    x = child;
    y = child->esq;
    x->esq = y->dir;

    if(y->dir != NULL)
        y->dir->pai = x;

    y->pai = x->pai;
    
    if(x->pai == NULL){
        *raiz = y;
    }

    else{

        if(x == x->pai->dir)
        x->pai->dir = y;

        else
        x->pai->esq = y;
    
    }

    y->dir = x;
    x->pai = y;
}

void preordemRB(Tree *t){
    if(!(t == NULL)){
        printf("%f - %s\t", t->reg.key, t->cor ? "black" : "red");
        preordemRB(t->esq); 
        preordemRB(t->dir); 
    }
}

void centalRB(Tree *t){
    if(!(t == NULL)){
        centalRB(t->esq); 
        printf("%f - %s\t", t->reg.key, t->cor ? "black" : "red");
        centalRB(t->dir); 
    }
}

void posordemRB(Tree *t){
    if(!(t == NULL)){
        posordemRB(t->esq); 
        posordemRB(t->dir); 
        printf("%f - %s\t", t->reg.key, t->cor ? "black" : "red");
    }
}