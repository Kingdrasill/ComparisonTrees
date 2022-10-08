#include "redblack.hpp"

RB* CreateRB(){
	return nullptr;
}

bool TVazia(RB **t){
    return *t == nullptr;
}


void pesquisaRB(RB **t, RB **aux, Record r){

	if(*t == nullptr){
        *aux = *t;
		return;
	}

	if((*t)->reg.key > r.key){ pesquisaRB(&(*t)->esq, aux, r); return;}
	if((*t)->reg.key < r.key){ pesquisaRB(&(*t)->dir, aux, r); return;}

	*aux = *t;
}

double isInRB(RB *t, Record r){
  
  if(t == nullptr){ 
    return 0;
  }
  
  return t->reg.key == r.key || isInRB(t->esq, r) || isInRB(t->dir, r);
}

void insertFixUpRB(RB **raiz, RB *child){
    RB *tio;

    while((child != *raiz) && (child->pai->cor == false)){
        
        if(child->pai == child->pai->pai->esq){
            
            tio = child->pai->pai->dir;

            //caso 1:
            if((tio != nullptr) && (tio->cor == false)){
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
            if((tio != nullptr) && (tio->cor == false)){
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


void insertRB(RB **t, RB **pai, RB **raiz, Record r){
    if(*t == nullptr){
        *t = new RB;
        (*t)->esq = nullptr; 
        (*t)->dir = nullptr; 
        (*t)->pai = pai != t ? *pai : nullptr;
        (*t)->cor = false; //false: vermelho  true:preto
        (*t)->reg = r; 
        insertFixUpRB(raiz, *t);  
    } else { 
        if(r.key < (*t)->reg.key){
            insertRB(&(*t)->esq, t, raiz, r);
            return;
        }
        
        if(r.key > (*t)->reg.key){
            insertRB(&(*t)->dir, t, raiz, r);
            return;
        }
    }
}

void rotacaoSimplesEsquerdaRB(RB **raiz, RB *child){
    RB *x, *y;

    x = child;
    y = child->dir;
    x->dir = y->esq;

    if(y->esq != nullptr)
        y->esq->pai = x;

    y->pai = x->pai;
    
    if(x->pai == nullptr)
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

void rotacaoSimplesDireitaRB(RB **raiz, RB *child){
    RB *x, *y;

    x = child;
    y = child->esq;
    x->esq = y->dir;

    if(y->dir != nullptr)
        y->dir->pai = x;

    y->pai = x->pai;
    
    if(x->pai == nullptr){
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

RB* minimumRB(RB **t) {
    if ((*t)->dir != nullptr){
        return minimumRB(&(*t)->dir);
    } else {
        return (*t);
    }
    return nullptr;
}

void transplantRB(RB **raiz, RB *u, RB *v) {
    if (u->pai == nullptr) {
        (*raiz) = v;
    } else if (u == u->pai->esq) {
        u->pai->esq = v;
    } else {
        u->pai->dir = v;
    }
    v->pai = u->pai;
}

void deleteFixUpRB(RB **raiz, RB *x) {
    while(x != *raiz && x->cor) {
        if (x == x->pai->esq) {
            RB *w = x->pai->dir;
            if(w != nullptr) {
                if (!w->cor) {
                    w->cor = true;
                    x->pai->cor = false;
                    rotacaoSimplesEsquerdaRB(raiz, x->pai);
                    w = x->pai->dir;
                }
                if ((w->dir==nullptr || w->dir->cor) && (w->esq==nullptr || w->esq->cor)) {
                    w->cor = false;
                    x = x->pai;
                } else if (w->dir==nullptr || w->dir->cor) {
                    w->esq->cor = true;
                    w->cor = false;
                    rotacaoSimplesDireitaRB(raiz, w);
                    w = x->pai->dir;
                }
                if (w->dir != nullptr && !w->dir->cor) {
                    w->cor = x->pai->cor;
                    x->pai->cor = true;
                    w->dir->cor = true;
                    rotacaoSimplesEsquerdaRB(raiz, x->pai);
                    x = (*raiz);
                }
            } 
            else
                x = x->pai;
        } else {
            RB *w = x->pai->esq;
            if(w != nullptr) {
                if (!w->cor) {
                    w->cor = true;
                    x->pai->cor = false;
                    rotacaoSimplesDireitaRB(raiz, x->pai);
                    w = x->pai->esq;
                }
                if ((w->dir==nullptr || w->dir->cor) && (w->esq==nullptr || w->esq->cor)) {
                    w->cor = false;
                    x = x->pai;
                } else if (w->esq==nullptr || w->esq->cor) {
                    w->dir->cor = true;
                    w->cor = false;
                    rotacaoSimplesEsquerdaRB(raiz, w);
                    w = x->pai->esq;
                }
                if (w->esq != nullptr && !w->esq->cor) {
                    w->cor = x->pai->cor;
                    x->pai->cor = true;
                    w->esq->cor = true;
                    rotacaoSimplesDireitaRB(raiz, x->pai);
                    x = (*raiz);
                }
            } 
            else
                x = x->pai;
        }
    }
    x->cor = true;
}

void deleteRB(RB **raiz, RB *z) {
    RB *y = z;
    RB *x;
    bool orginalColor = y->cor;
    if (z->esq == nullptr) {
        x = z->dir;
        if(x == nullptr) {
            x = new RB;
            x->reg.key = -1;
            x->cor = true;
            z->dir = x;
        }
        transplantRB(raiz, z, z->dir);
        x->pai = z->pai;
    } else if (z->dir == nullptr) {
        x = z->esq;
        if(x == nullptr) {
            x = new RB;
            x->reg.key = -1;
            x->cor = true;
            z->esq = x;
        }
        transplantRB(raiz, z, z->esq);
        x->pai = z->pai;
    } else {
        y = minimumRB(&z->esq);
        orginalColor = y->cor;
        x = y->esq;
        if(x == nullptr) {
            x = new RB;
            x->reg.key = -1;
            x->cor = true;
            y->esq = x;
        }
        if(y->pai == z) {
            x->pai = y;
        } else {
            transplantRB(raiz, y, y->esq);
            y->esq = z->esq;
            y->esq->pai = y;
        }
        transplantRB(raiz, z, y);
        y->dir = z->dir;
        y->dir->pai = y;
        y->cor = z->cor;
    }
    RB *aux = x;
    if (orginalColor) {
        deleteFixUpRB(raiz, aux);
    }
    if(aux->reg.key == -1) {
        if(aux == aux->pai->esq)
            aux->pai->esq = nullptr;
        else
            aux->pai->dir = nullptr;
        delete aux;
    }
    delete z;
}

void removeRB(RB **t, RB **raiz, Record r) {  	
  	if (*t == nullptr){ 
  		printf("[ERROR]: Record not found!!!\n");
    	return;
  	}

  	if (r.key < (*t)->reg.key){ removeRB(&(*t)->esq, raiz, r); return;}
  	if (r.key > (*t)->reg.key){ removeRB(&(*t)->dir, raiz, r); return;}
    
    if ((*raiz)->esq == nullptr && (*raiz)->dir == nullptr) { delete (*raiz); (*raiz) = nullptr; return;}
    
    deleteRB(raiz, (*t));
}

void preordemRB(RB *t){
    if(!(t == nullptr)){
        printf("%f - %s\t", t->reg.key, t->cor ? "black" : "red");
        preordemRB(t->esq); 
        preordemRB(t->dir); 
    }
}

void centralRB(RB *t){
    if(!(t == nullptr)){
        centralRB(t->esq); 
        printf("%f - %s\t", t->reg.key, t->cor ? "black" : "red");
        centralRB(t->dir); 
    }
}

void posordemRB(RB *t){
    if(!(t == nullptr)){
        posordemRB(t->esq); 
        posordemRB(t->dir); 
        printf("%f - %s\t", t->reg.key, t->cor ? "black" : "red");
    }
}

void widthPathRB(RB *t){
    std::queue<RB*> q;
    RB  *no, *filho;
    int qtd = 0, p = 1, f = 0;
    no = t;
    q.push(no);
    
    while (!q.empty()){
        qtd += 1;
        no = q.front();
        q.pop();
        printf("%f - %s\t", no->reg.key, no->cor ? "black" : "red");
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

std::chrono::microseconds insercaoRB(int size, std::vector<double> numbers, RB **t) {
    Record r;
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) {
        r.key = numbers[i];
        insertRB(&(*t), &(*t), &(*t), r);
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::chrono::microseconds searchRB(std::vector<double> numbers, RB **t, std::vector<double> *remover) {
    Record r;
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<10000; i++) {
        r.key = numbers[i];
        RB *aux;
        pesquisaRB(t, &aux, r);
        if(aux != nullptr) {
            std::cout << std::setprecision(12) << aux->reg.key << std::endl;
            remover->push_back(aux->reg.key);
        }
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::chrono::microseconds remocaoRB(std::vector<double> numbers, RB **t) {
    Record r;
    std::chrono::_V2::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(double x:numbers) {
        r.key = x;
        removeRB(t, t, r);
    }
    std::chrono::_V2::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}