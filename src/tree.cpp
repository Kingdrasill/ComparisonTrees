#include "tree.hpp"

Tree* CreateTree(){
	return nullptr;
}

bool TVazia(Tree **t){
    return *t == nullptr;
}

void insertTree(Tree **t, Record r){
    if(TVazia(t)){
        *t = new Tree;
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
        *aux = *t;
        return;
    }

    if((*t)->reg.key > r.key){ pesquisa(&(*t)->esq, aux, r); return;}
    if((*t)->reg.key < r.key){ pesquisa(&(*t)->dir, aux, r); return;}

    *aux = *t;
}


double isInTree(Tree *t, Record r) {
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
    delete aux;
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
    	delete aux;
        return;
  	}

  	if ((*t)->esq != nullptr){ antecessor(&(*t)->esq, *t); return; }

  	aux = *t;  
  	*t = (*t)->dir;
  	delete aux;
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
    int qtd = 0, p = 1, f = 0;
    no = t;
    q.push(no);
    
    while (!q.empty()){
        qtd += 1;
        no = q.front();
        q.pop();
        printf("%f\t", no->reg.key);
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

std::chrono::microseconds insercaoTree(int size, std::vector<double> numbers, Tree **t) {
    Record r;
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) {
        r.key = numbers[i];
        insertTree(&(*t), r);
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::chrono::microseconds searchTree(std::vector<double> numbers, Tree **t, std::vector<double> *remover) {
    Record r;
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<10000; i++) {
        r.key = numbers[i];
        Tree *aux;
        pesquisa(t, &aux, r);
        if(aux != nullptr) {
            std::cout << std::setprecision(12) << aux->reg.key << std::endl;
            remover->push_back(aux->reg.key);
        }
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::chrono::microseconds remocaoTree(std::vector<double> numbers, Tree **t) {
    Record r;
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(double x:numbers) {
        r.key = x;
        removeTree(t, r);
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}