#include <stdio.h>
#include <stdlib.h>
#include "lib_lista.h"
int inicializa_lista(t_lista *l) {

	t_nodo *ini, *fim;
	
	ini = (t_nodo *)malloc(sizeof(t_nodo));
	if (ini == NULL)
		return 0;

	fim = (t_nodo *)malloc(sizeof(t_nodo));
	if (fim == NULL) {
		free (ini);
		return 0;
	}

	l->ini = ini;
	l->fim = fim;

	ini->prox = fim;
	ini->prev = NULL;

	fim->prev = ini;
	fim->prox = NULL;
	
	l->atual = NULL;

	l->tam = 0;
	
	return 1;
}

int lista_vazia(t_lista *l) {

	if (l->tam == 0)
		return 1;
	return 0;
}
void destroi_lista(t_lista *l) {

	t_nodo *aux;

	aux = l->ini->prox;
	if (! lista_vazia(l)) {
		while (aux->prox != NULL) {
			aux = aux->prox;
			free (aux->prev);
			l->tam--;
		}
	}
	free (l->fim);
	free (l->ini);
}
int insrlista(int linha, int coluna, t_lista *l){

	t_nodo *new;

	new = (t_nodo *)malloc(sizeof(t_nodo));
	if (new == NULL)
		return 0;

	l->tam++;

	new->chave.x = linha;
	new->chave.y = coluna;

	new->status = VIVO;

	new->prox = l->fim;
	new->prev = l->fim->prev;

	new->prev->prox = new;
	l->fim->prev = new;

	return 1;
}
/*int remove_inicio_lista(int *item, t_lista *l) {
	
	if (lista_vazia (l))
		return 0;

	*item = l->ini->prox->chave;

	l->ini->prox = l->ini->prox->prox;
	free (l->ini->prox->prev);
	l->ini->prox->prev = l->ini;

	l->tamanho--;
	
	return 1;
}*/
/*int pertence_lista(int chave, t_lista *l) {

	t_nodo *aux;
	
	if (lista_vazia (l))
		return 0;

	aux = l->ini->prox;
	l->fim->chave = chave;

	while (aux->chave != chave) 
		aux = aux->prox;

	if (aux == l->fim)
		return 0;
	return 1;
}*/
int inicializa_atual_inicio(t_lista *l) {

	if (lista_vazia(l))
		return 0;

	l->atual = l->ini->prox;
	return 1;
}
int incrementa_atual(t_lista *l) {

	/*se a lista não estiver vazia*/
	if (lista_vazia(l)) return 0;
	
	if (l->atual == l->fim->prev) return 0;

	l->atual = l->atual->prox;
	
	return 1;
}
int consulta_item_atual(t_coord *item, t_lista *l) {

	if (lista_vazia(l))
		return 0;

	*item = l->atual->chave;
	return 1;
}
int remove_item_atual(t_coord *item, t_lista *l) {

	t_nodo *p;

	if (lista_vazia(l))
		return 0;

	*item = l->atual->chave;

	p = l->atual;	

	l->atual->prev->prox = l->atual->prox;
	l->atual->prox->prev = l->atual->prev;

	if (l->atual->prox == l->fim) {
		l->atual = l->atual->prev;
	}	
	else
		l->atual = l->atual->prox;
		
	l->tam--;
	free (p);

	return 1;
}
