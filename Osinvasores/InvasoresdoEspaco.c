#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "spinv.h"
#include <time.h>

int main () {

	initscr();
	noecho ();
	curs_set (FALSE);
	nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */

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

	t_listaTiros l_tiros,l_tirosA;
	t_listAliens l_aliens;
	t_listaBarreira l_barreira;

	inicializa_barreira (&l_barreira, telalinhas, telacolunas);
	inicializa_aliens (&l_aliens);
	initiros (&l_tiros);
	initiros (&l_tirosA);

	int linha_alien = 8; 			/*Em qual linha, primeiramente, eu escrevo o alien*/
	int coluna_alien = 1; 			/*Em qual coluna, primeiramente,  eu escrevo o alien*/
	int player_linha = telalinhas-2;
	int player_coluna = telacolunas/2;
	int versao = 0; 			/*Versão que é para imprimir do alien*/
	int indo = 1; 				/*controla se o alien esta indo ou vindo*/
	int contiros = 0; 			/*quantidade de tiros na tela*/
	char key;
	int cnt = 0;
	int prdaliens = 20000;			/*Servira para controlar o periodo do alien*/ 
	int prdtiros = prdaliens/8;		/*periodo dos tiro (8x mais rapido que os aliens)*/
	int prdtirosA = prdaliens/4;
	int situacao;
	int contirosA = 5;      		/*quantida de tiros dos aliens*/ 

	t_controle linhasvivas, colunasvivas;

	inicializa_controle (&linhasvivas,&colunasvivas);
	

	/*win = newwin (38,100,0,0);
	box(win, 0, 0);
	wrefresh(win);*/

	while (1) {

		while (cnt <= PERIODODOJOGO) {

			key = getch ();
		 	if (key == 'd') {
				if (player_coluna + 1 < telacolunas){
					player_coluna++;
				}
			}
			else if (key == 'a') {
				if (player_coluna - 1 > 0)
					player_coluna--;
			}
			else if (key == ' ') {
				if (contiros < QNTDTIROS) {
					contiros++;
					instiroslista (&l_tiros,player_linha-1,player_coluna+2);
				}
			}
			else if (key == 'q') {
				endwin();
				return 0;
			}

			if ((cnt % prdaliens) == 0 ) {
				admimpressao (&l_aliens,corposaliens,&indo,&versao,&linha_alien,&coluna_alien,&linhasvivas,&colunasvivas,telalinhas,telacolunas);
			}
			else if (cnt == RESETACONTADOR)
				cnt = 0;
			
			if ((cnt % prdtiros) == 0) {
				
				t_tiro *tiro;
				tiro = l_tiros.ini->prox;
				while (tiro->prox != NULL) {

					situacao = detecta_tiro (&tiro->chave,&tiro->status,&l_aliens,&l_barreira,linha_alien,coluna_alien);
					analizasituacao (situacao,&tiro->chave,&l_aliens,&l_barreira,corposaliens,&versao,&coluna_alien,&linha_alien,&contiros); 
					prntaliens (&l_aliens,corposaliens,&versao,&linha_alien,&coluna_alien);

					if (situacao >= 1 && situacao <= 5)
						srchandrmtirolista (&l_tiros);
					tiro = tiro->prox;
				}	
				prntiro (&l_tiros,contiros);
			}

			/*if ((cnt % prdtirosA) == 0){
				
				int i;
				t_coord *coordbomba;

				srand(time(NULL));
				if (l_aliens->tam > 5) {
					for (i = contirosA - l_tirosA->tam; i < QNTDALIENTIROS; i++) {
						alien = rand % l_aliens->tam;					 sorteia um alien da lista para atirar;
						coordbomba = srchalien (alien,l_aliens);
						instiroslista = (l_tirosA,coordbomba.x,coordbomba.y);
					}
				}
				else {
					for (i = l_aliens->tam; i < l_tirosA; i++ ) {
						alien = rand % l_alien->tam;	
						coordbomba = srchalien (alien,l_aliens,linha_alien,coluna_alien);
						instiroslista = (l_tirosA,coordbomba.x,coordbomba.y);
				}
				while parecido com o tiro player
			
			}*/
			prntplayer (corpoplayer,&player_linha,&player_coluna);
				
		/*	refresh ();*/

			prntbarreiras (&l_barreira);
			cnt ++;

			refresh ();

		}	
	}
	/*For the time being, that's all folks*/

	return 0;

}
