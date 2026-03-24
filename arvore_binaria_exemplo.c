#include <stdio.h>
#include <stdlib.h>

struct No{
	int valor;
	struct No *esq;
	struct No *dir;
};

struct No* inserir(struct No* raiz, int valor){
	
	if (raiz == NULL){
		struct No* novo = (struct No*)malloc(sizeof(struct No));
		novo->valor = valor;
		novo->esq = novo->dir = NULL;
		return novo;
	}
	
	if (valor < raiz->valor){
		raiz->esq = inserir(raiz->esq, valor);
	} else {
		raiz->dir = inserir(raiz->dir, valor);
	}
	
	return raiz;
}

void imprimirEmOrdem(struct No* raiz) {
	if (raiz != NULL){
		imprimirEmOrdem(raiz->esq);
		printf("%d ", raiz->valor);
		imprimirEmOrdem(raiz->dir);
	}
}

int main(){
	
	struct No* raiz = NULL;
	
	raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    
    printf("Arvore em ordem (deve aparecer ordenado): \n");
    imprimirEmOrdem(raiz);
    printf("\n");
	
	return 0;
}
