#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "spinv.h"

int main () {

	initscr();
	curs_set (FALSE);
	/*WINDOW *win;*/


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

	char **corpoplayer;
	corpoplayer = (char **)malloc(sizeof(char *)*ALTURAPLAYER);
	for (i = 0; i < ALTURAPLAYER; i++) 
		corpoplayer[i] = (char *)malloc(sizeof(char)*TAMPLAYER);

	initspritsaliens (corposaliens); /* inicializa os corpos dos aliens */
	initspritplayer (corpoplayer); /*inicializa o corpo do player*/

	t_listAliens l_aliens;

	inicializa_aliens (&l_aliens);

	int linha_alien = 8; /*Em qual linha, primeiramente, eu escrevo o alien*/
	int coluna_alien = 1; /*Em qual coluna, primeiramente,  eu escrevo o alien*/
	int player_linha = telalinhas-2;
	int player_coluna = telacolunas/2;
	int versao = 0; /*Versão que é para imprimir do alien*/
	int indo = 1; /*controla se o alien esta indo ou vindo*/

	t_controle linhasvivas, colunasvivas;

	inicializa_controle (&linhasvivas,&colunasvivas);

	/*win = newwin (38,100,0,0);
	box(win, 0, 0);
	wrefresh(win);*/

	while (1) {

		clear ();

		/*key = getch ();*/

		admimpressao (&l_aliens,corposaliens,&indo,&versao,&linha_alien,&coluna_alien,&linhasvivas,&colunasvivas,telalinhas,telacolunas);
	
		prntplayer (corpoplayer,&player_linha,&player_coluna);
		
		refresh ();
		
		usleep (DELAY);

		versao = (versao + 1)/2;

	}
	/*For the time being, that's all folks*/

	return 0;

}
