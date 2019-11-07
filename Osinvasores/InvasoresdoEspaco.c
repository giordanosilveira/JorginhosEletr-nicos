#include <ncurses.h>
#include "spinv.h"

int main () {

  	initscr();


	int tam_linhas, tam_colunas;

	getmaxyx (tam_linhas, tam_colunas);
	if (tam_colunas < MINCOLUNAS || tam_linhas < MIMLINHAS) {
		printf ("O terminal deve ter no mínimo 38 linhas por 100 colunas\n");
		endwin ();
		return 1;
	}

	char  **corposaliens,i;
	corposaliens = (int **)malloc(sizeof(int*)*QNTCORPOS);

	for (i = 0; i < QNTCORPOS; i++) {
		corposaliens[i] = (int *)malloc(sizeof(int)*TAMET);
	}
	initspritsalien(corposaliens); /*inicializa os corpos dos aliens*/

	t_listAliens l_aliens;

	initaliens (l_aliens);

	prntaliens ()
	/*For the time being, that's all folks*/



































}
