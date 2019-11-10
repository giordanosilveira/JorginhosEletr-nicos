#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "spinv.h"
int main () {

	initscr();
	curs_set (FALSE);

	int telalinhas, telacolunas; /*resposável por pegar o tamanho da tela*/

	getmaxyx (stdscr, telalinhas, telacolunas);
	if (telacolunas < MINCOLUNAS || telalinhas < MINLINHAS) {
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

	initspritsaliens (corposaliens); /* inicializa os corpos dos aliens */

	t_listAliens l_aliens;

	inicializa_aliens (&l_aliens);

	int linha_alien = 8; /*Em qual linha, primeiramente, eu escrevo o alien*/
	int coluna_alien = 1; /*Em qual coluna, primeiramente,  eu escrevo o alien*/
	int versao = 0; /*Versão que é para imprimir do alien*/
	int indo = 1; /*controla se o alien esta indo ou vindo*/

	t_controle linhavivas, colunvivas;

	inicializa_controle (&linhavivas,&colunavivas);

	while (1) {

		clear ();

		admimpressao (&l_aliens,corposaliens,&indo,&versao,&linha_alien,&coluna_alien,&linhasvivas,&colunasvivas,telalinhas,telacolunas);

		refresh ();
		
		usleep (DELAY);

	}
	/*For the time being, that's all folks*/

	return 0;

}
