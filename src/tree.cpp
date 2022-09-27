#include "tree.hpp"

Tree* CreateTree(){
	return nullptr;
}

bool TVazia(Tree **t){
    return *t == nullptr;
}

void insertTree(Tree **t, Record r){
    if(TVazia(t)){
        *t = (Tree*)malloc(sizeof(Tree));
        (*t)->esq = nullptr; 
        (*t)->dir = nullptr; 
        (*t)->reg = r; 
    } else {
        if(r.key < (*t)->reg.key){
            insertTree(&(*t)->esq, r);
        }

        if(r.key > (*t)->reg.key){
            insertTree(&(*t)->dir, r);
        }
    }
}

void pesquisa(Tree **t, Tree **aux, Record r){
    if(*t == nullptr){
      printf("[ERROR]: Node not found!");
      return;
    }

    if((*t)->reg.key > r.key){ pesquisa(&(*t)->esq, aux, r); return;}
    if((*t)->reg.key < r.key){ pesquisa(&(*t)->dir, aux, r); return;}

    *aux = *t;
}


int isInTree(Tree *t, Record r) {
    if(t == nullptr){ 
      return 0;
    }
    
    return t->reg.key == r.key || isInTree(t->esq, r) || isInTree(t->dir, r);
}


void antecessor(Tree **t, Tree *aux){ 
	if ((*t)->dir != nullptr){ 
		antecessor(&(*t)->dir, aux);
		return;
    }
    
    aux->reg = (*t)->reg;
    aux = *t; 
    *t = (*t)->esq;
    free(aux);
} 


void removeTree(Tree **t, Record r){
	Tree *aux;
  	
  	if (*t == nullptr){ 
  		printf("[ERROR]: Record not found!!!\n");
    	return;
  	}

  	if (r.key < (*t)->reg.key){ removeTree(&(*t)->esq, r); return; }
  	if (r.key > (*t)->reg.key){ removeTree(&(*t)->dir, r); return; }

  	if ((*t)->dir == nullptr){ 
  		aux = *t;  
  		*t = (*t)->esq;
    	free(aux);
        return;
  	}

  	if ((*t)->esq != nullptr){ antecessor(&(*t)->esq, *t); return; }

  	aux = *t;  
  	*t = (*t)->dir;
  	free(aux);
}


void preordem(Tree *t)
{
    if(!(t == nullptr)){
        printf("%f ", t->reg.key);
        preordem(t->esq); 
        preordem(t->dir); 
    }
}


void central(Tree *t)
{
    if(!(t == nullptr)){
        central(t->esq); 
        printf("%f ", t->reg.key);
        central(t->dir); 
    }
}

void posordem(Tree *t)
{
    if(!(t == nullptr)){
        posordem(t->esq); 
        posordem(t->dir); 
        printf("%f ", t->reg.key);
    }
}

void widthPath(Tree *t){
    std::queue<Tree*> q;
    Tree  *no, *filho;
    int qtd = 0;
    no = t;
    q.push(no);
    
    while (!q.empty()){
        qtd += 1;
        no = q.front();
        q.pop();
        printf("%f ", no->reg.key);
        if(no->esq != nullptr){
            filho = no->esq;
            q.push(filho);
        }
        if(no->dir != nullptr){
            filho= no->dir;
            q.push(filho);
        }
    }
    printf("\n%d\n", qtd);
}