#include <stdio.h>
#include <stdlib.h>

#include "lib_lista.h"
int inicializa_lista(t_listAliens *l) {

	t_alien *ini, *fim;
	
	ini = (t_alien *)malloc(sizeof(t_alien));
	if (ini == NULL)
		return 0;

	fim = (t_alien *)malloc(sizeof(t_alien));
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
	
	return 1;
}

/*void destroi_lista(t_listAliens *l) {

	t_alien *aux;

	aux = l->ini->prox;
	if (! lista_vazia(l)) {
		while (aux->prox != NULL) {
			aux = aux->prox;
			free (aux->prev);
			l->tamanho--;
		}
	}
	free (l->fim);
	free (l->ini);
}*/

int insere_fim_lista(t_listAliens *l, int x; int y){

	t_alien *et;

	et = (t_alien *)malloc(sizeof(t_alien));
	if (et == NULL)
		return 0;

	et->status = VIVO
	et->versao = 0;

	et->pos.x = x;
	et->pos.y = y;

	et->prev = l->fim->prev;

	et->prev->prox = et;
	l->fim->prev = et;

	return 1;
}
