#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "spinv.h"

int main () {

	initscr();
	curs_set (FALSE);
	/*nodelay(stdscr, TRUE);*/  /* faz com que getch não aguarde a digitação */

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

	t_listaTiros l_tiros;
	t_listAliens l_aliens;

	inicializa_aliens (&l_aliens);

	int linha_alien = 8; /*Em qual linha, primeiramente, eu escrevo o alien*/
	int coluna_alien = 1; /*Em qual coluna, primeiramente,  eu escrevo o alien*/
	int player_linha = telalinhas-2;
	int player_coluna = telacolunas/2;
	int versao = 0; /*Versão que é para imprimir do alien*/
	int indo = 1; /*controla se o alien esta indo ou vindo*/
	int contiros = 0; /*quantidade de tiros na tela*/
	char key;
	int cnt = 0;

	t_tiro tiros[QNTDTIROS];

	t_controle linhasvivas, colunasvivas;

	inicializa_controle (&linhasvivas,&colunasvivas);

	/*initiros (&l_tiros);*/

	/*win = newwin (38,100,0,0);
	box(win, 0, 0);
	wrefresh(win);*/

	while (1) {

		clear ();

		key = getch ();
		if (key == ' ') {
			contiros++;
			/*if (contiros <= l_tiros->tam)
				instiroslista ();*/
		}
		else if (key == 'd') {
			player_coluna++;
		}
		else if (key == 'a') {
			player_coluna--;
		}
	/*	else if (key == 'p'){ */
			/*pausa*/
		/*}
		else if (key == 'q') {*/
			/*acabou*/
		/*}*/

		if (cnt == 10000)
			admimpressao (&l_aliens,corposaliens,&indo,&versao,&linha_alien,&coluna_alien,&linhasvivas,&colunasvivas,telalinhas,telacolunas);
	
		prntplayer (corpoplayer,&player_linha,&player_coluna);
	
	/*	prntiro (key,tiros,&contiros);*/

		refresh ();
	
		if (cnt > 20000)
			cnt = 0;
		cnt ++;

		versao = (versao + 1)/2;

	}
	/*For the time being, that's all folks*/

	return 0;

}
