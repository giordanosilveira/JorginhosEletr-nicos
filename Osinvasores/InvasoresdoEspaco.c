#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "spinv.h"

int main () {

  	initscr();


	int tam_linhas, tam_colunas; /*resposável por pegar o tamanho da tela*/

	getmaxyx (stdscr, tam_linhas, tam_colunas);
	if (tam_colunas < MINCOLUNAS || tam_linhas < MINLINHAS) {
		printf ("O terminal deve ter no mínimo 38 linhas por 100 colunas\n");
		endwin ();
		return 1;
	}

	char  **corposaliens;
	int i;
	corposaliens = (char **)malloc(sizeof(char*)*SPRITSALIEN);

	for (i = 0; i < SPRITSALIEN; i++) {
		corposaliens[i] = (char *)malloc(sizeof(char)*TAMALIEN);
	}
	
	initspritsaliens (corposaliens); /*inicializa os corpos dos aliens*/

	t_listAliens l_aliens;

	initaliens (&l_aliens);

	while (1) {

		clear ();
/*	admimpressao ();*/

		prntaliens (&l_aliens,corposaliens);
		refresh ();

		usleep (DELAY);

	}
	/*For the time being, that's all folks*/



































}
