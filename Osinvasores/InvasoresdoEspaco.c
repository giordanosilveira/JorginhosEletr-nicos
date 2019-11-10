#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "spinv.h"
void initspritsaliens (char **c_aliens) {

	strcpy (c_aliens[0],ALIEN11);
        strcpy (c_aliens[1],ALIEN12);
        strcpy (c_aliens[2],ALIEN13);
        strcpy (c_aliens[3],ALIEN112);
        strcpy (c_aliens[4],ALIEN122);
        strcpy (c_aliens[5],ALIEN132);

        strcpy (c_aliens[6],ALIEN21);
        strcpy (c_aliens[7],ALIEN22);
        strcpy (c_aliens[8],ALIEN23);
        strcpy (c_aliens[9],ALIEN212);
        strcpy (c_aliens[10],ALIEN222);
        strcpy (c_aliens[11],ALIEN232);

        strcpy (c_aliens[12],ALIEN31);
        strcpy (c_aliens[13],ALIEN32);
        strcpy (c_aliens[14],ALIEN33);
 	strcpy (c_aliens[15],ALIEN312);
 	strcpy (c_aliens[16],ALIEN322);
	strcpy (c_aliens[17],ALIEN332);
}
int main () {

  	initscr();


	int tam_linhas, tam_colunas; /*resposável por pegar o tamanho da tela*/

	getmaxyx (stdscr, tam_linhas, tam_colunas);
	if (tam_colunas < MINCOLUNAS || tam_linhas < MINLINHAS) {
		printf ("O terminal deve ter no mínimo 38 linhas por 100 colunas\n");
		endwin ();
		return 1;
	}

/*	char  **corposaliens;
	int i;
	corposaliens = (char **)malloc(sizeof(char*)*SPRITSALIEN);

	for (i = 0; i < SPRITSALIEN; i++) {
		corposaliens[i] = (char *)malloc(sizeof(char)*TAMALIEN);
	}
	
	initspritsaliens (corposaliens); inicializa os corpos dos aliens

	t_listAliens l_aliens;

	initaliens (&l_aliens);

	while (1) {

		clear ();
	admimpressao ();

		prntaliens (&l_aliens,corposaliens);
		refresh ();

		usleep (DELAY);

	}
	For the time being, that's all folks


































*/
}
