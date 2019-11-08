#include <stdio.h>
#include <stdlib.h>

#include "lib_lista.h"
void initaliens (t_listAliens *l) {

	t_alien *ini, *fim;
	
	ini = (t_alien *)malloc(sizeof(t_alien));
	if (ini != NULL){
		fim = (t_alien *)malloc(sizeof(t_alien));
		if (fim != NULL) {
	
			l->ini = ini;
			l->fim = fim;

			ini->prox = fim;
			ini->prev = NULL;

			fim->prev = ini;
			fim->prox = NULL;
		}
		else 
			free (ini);
	}
	
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

void insalienslista (t_listAliens *l, int x; int y){

	t_alien *et;

	et = (t_alien *)malloc(sizeof(t_alien));
	if (et != NULL) {

		et->status = VIVO
		et->versao = 0;

		et->pos.x = x;
		et->pos.y = y;

		et->prev = l->fim->prev;

		et->prev->prox = et;
		l->fim->prev = et;
	}

}
