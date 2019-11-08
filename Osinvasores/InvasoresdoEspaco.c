#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "spinv.h"

int main () {

  	initscr();


	int tam_linhas, tam_colunas; /*resposável por pegar o tamanho da tela*/

	getmaxyx (tam_linhas, tam_colunas);
	if (tam_colunas < MINCOLUNAS || tam_linhas < MIMLINHAS) {
		printf ("O terminal deve ter no mínimo 38 linhas por 100 colunas\n");
		endwin ();
		return 1;
	}

	char  **corposaliens,i;
	corposaliens = (int **)malloc(sizeof(int*)*SPRITSALIEN);

	for (i = 0; i < QNTCORPOS; i++) {
		corposaliens[i] = (int *)malloc(sizeof(int)*TAMALIEN);
	}
	initspritsalien(corposaliens); /*inicializa os corpos dos aliens*/

	t_listAliens l_aliens;

	initaliens (&l_aliens);

	while (1)

		clear ();
/*	admimpressao ();*/

		prntaliens (&l_aliens,corposaliens);
		refresh ();

		usleep (DELAY);

	}
	/*For the time being, that's all folks*/



































}
