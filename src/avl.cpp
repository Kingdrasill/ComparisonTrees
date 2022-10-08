#include "avl.hpp"

AVL* CreateAVL(){
	return nullptr;
}

bool TVazia(AVL **t){
    return *t == nullptr;
}

void insertAVL(AVL **t, Record r){
    if(*t == nullptr){
        *t = new AVL;
        (*t)->esq = nullptr; 
        (*t)->dir = nullptr; 
        (*t)->weight = 0;
        (*t)->reg = r; 

    } else {
        if(r.key < (*t)->reg.key){
            insertAVL(&(*t)->esq, r);
            if ((getWeight(&(*t)->esq) - getWeight(&(*t)->dir)) == 2){
                if(r.key < (*t)->esq->reg.key)
                    rotacaoSimplesDireitaAVL(t);
                else
                    rotacaoDuplaDireitaAVL(t);
            }
        }
        if(r.key > (*t)->reg.key){
            insertAVL(&(*t)->dir, r);
            if ((getWeight(&(*t)->dir) - getWeight(&(*t)->esq)) == 2){
                if(r.key > (*t)->dir->reg.key)
                    rotacaoSimplesEsquerdaAVL(t);
                else
                    rotacaoDuplaEsquerdaAVL(t);
            }
        }
    
    }
    (*t)->weight = getMaxWeight(getWeight(&(*t)->esq), getWeight(&(*t)->dir)) + 1;
}

void pesquisaAVL(AVL **t, AVL **aux, Record r){

	if(*t == nullptr){
        *aux = *t;
		return;
	}

	if((*t)->reg.key > r.key){ pesquisaAVL(&(*t)->esq, aux, r); return;}
	if((*t)->reg.key < r.key){ pesquisaAVL(&(*t)->dir, aux, r); return;}

	*aux = *t;
}

double isInAVL(AVL *t, Record r){
  
  if(t == nullptr){ 
    return 0;
  }
  
  return t->reg.key == r.key || isInAVL(t->esq, r) || isInAVL(t->dir, r);
}

void antecessorAVL(AVL **t, AVL *aux){ 

	if ((*t)->dir != NULL){ 
		antecessorAVL(&(*t)->dir, aux);
		return;
  	}
  	
  	aux->reg = (*t)->reg;
  	aux = *t; 
  	*t = (*t)->esq;
  	delete aux;
}

void rebalanceAVL(AVL **t){
	int balance;
  	int esq = 0;
  	int dir = 0;

	balance = getWeight(&(*t)->esq) - getWeight(&(*t)->dir);
	if((*t)->esq)
		esq = getWeight(&(*t)->esq->esq) - getWeight(&(*t)->esq->dir);
	if((*t)->dir)
		dir = getWeight(&(*t)->dir->esq) - getWeight(&(*t)->dir->dir);

	if(balance == 2 && esq >= 0)
		rotacaoSimplesDireitaAVL(t);
	if(balance == 2 && esq < 0)
		rotacaoDuplaDireitaAVL(t);

	if(balance == -2 && dir <= 0)
		rotacaoSimplesEsquerdaAVL(t);
	if(balance == -2 && dir > 0)
		rotacaoDuplaEsquerdaAVL(t); 	

}

void removeAVL(AVL **t, AVL **f, Record r){
	AVL *aux;
  	
  	if (*t == nullptr){ 
  		printf("[ERROR]: Record not found!!!\n");
    	return;
  	}

  	if (r.key < (*t)->reg.key){ removeAVL(&(*t)->esq, t, r); return;}
  	if (r.key > (*t)->reg.key){ removeAVL(&(*t)->dir, t, r); return;}

  	if ((*t)->dir == nullptr){ 
  		aux = *t;  
  		*t = (*t)->esq;
    	delete aux;
    	rebalanceAVL(f);
    	return;
  	}

  	if ((*t)->esq != nullptr){ 
  		antecessorAVL(&(*t)->esq, *t);
  		rebalanceAVL(t);
  		rebalanceAVL(f);
  		return;
  	}

  	aux = *t;  
  	*t = (*t)->dir;
  	delete aux;
  	rebalanceAVL(t);
  	rebalanceAVL(f); 	
  	
}

void preordemAVL(AVL *t)
{
  if(!(t == nullptr)){
    printf("%f:%d\t", t->reg.key, t->weight);
    preordemAVL(t->esq); 
    preordemAVL(t->dir); 
  }
}


void centralAVL(AVL *t)
{
  if(!(t == nullptr)){
    centralAVL(t->esq); 
    printf("%f:%d\t", t->reg.key, t->weight);
    centralAVL(t->dir); 
  }
}

void posordemAVL(AVL *t)
{
  if(!(t == nullptr)){
    posordemAVL(t->esq); 
    posordemAVL(t->dir); 
    printf("%f:%d\t", t->reg.key, t->weight);
  }
}

void widthPathAVL(AVL *t){
    std::queue<AVL*> q;
    AVL  *no, *filho;
    int qtd = 0, p = 1, f = 0;
    no = t;
    q.push(no);
    
    while (!q.empty()){
        qtd += 1;
        no = q.front();
        q.pop();
        printf("%f:%d\t", no->reg.key, no->weight);
        p--;
		if(no->esq != nullptr){
            filho = no->esq;
            q.push(filho);
			f++;
        }
        if(no->dir != nullptr){
            filho= no->dir;
            q.push(filho);
			f++;
        }
		if(p == 0) {
			printf("\n");
			p = f;
			f = 0;
		}
    }
}

int getWeight(AVL **t){
	if(*t == nullptr)
		return -1;
	return (*t)->weight;
}

int getMaxWeight(int esq, int dir){
	if(esq > dir)
		return esq;
	return dir;
}

void rotacaoSimplesDireitaAVL(AVL **t){
	AVL *aux;
	aux = (*t)->esq;
	(*t)->esq = aux->dir;
	aux->dir = (*t);
	(*t)->weight = getMaxWeight(getWeight(&(*t)->esq), getWeight(&(*t)->dir)) + 1;
	aux->weight  = getMaxWeight(getWeight(&aux->esq), (*t)->weight) + 1;
	(*t) = aux;
}

void rotacaoSimplesEsquerdaAVL(AVL **t){
	AVL *aux;
	aux = (*t)->dir;
	(*t)->dir = aux->esq;
	aux->esq = (*t);
	(*t)->weight = getMaxWeight(getWeight(&(*t)->esq), getWeight(&(*t)->dir)) + 1;
	aux->weight  = getMaxWeight(getWeight(&aux->esq), (*t)->weight) + 1;
	(*t) = aux;
}

void rotacaoDuplaDireitaAVL(AVL **t){
	rotacaoSimplesEsquerdaAVL(&(*t)->esq);
	rotacaoSimplesDireitaAVL(t);
}

void rotacaoDuplaEsquerdaAVL(AVL **t){
	rotacaoSimplesDireitaAVL(&(*t)->dir);
	rotacaoSimplesEsquerdaAVL(t);
}

std::chrono::microseconds insercaoAVL(int size, std::vector<double> numbers, AVL **t) {
    Record r;
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) {
        r.key = numbers[i];
        insertAVL(&(*t), r);
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::chrono::microseconds searchAVL(std::vector<double> numbers, AVL **t, std::vector<double> *remover) {
    Record r;
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<10000; i++) {
        r.key = numbers[i];
        AVL *aux;
        pesquisaAVL(t, &aux, r);
        if(aux != nullptr) {
            std::cout << std::setprecision(12) << aux->reg.key << std::endl;
            remover->push_back(aux->reg.key);
        }
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::chrono::microseconds remocaoAVL(std::vector<double> numbers, AVL **t) {
    Record r;
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(double x:numbers) {
        r.key = x;
        removeAVL(t, t, r);
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}