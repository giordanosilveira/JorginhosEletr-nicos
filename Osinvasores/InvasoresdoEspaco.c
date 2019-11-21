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

	char **corponavemae;
	corponavemae = (char **)malloc(sizeof(char*)*ALTURANAVEMAE);
	for (i = 0; i < ALTURANAVEMAE; i++)
		corponavemae[i] = (char*)malloc(sizeof(char)*LARGURANAVEMAE);
	

	initspritsaliens (corposaliens); 	/* inicializa os corpos dos aliens */
	initspritplayer (corpoplayer); 		/*inicializa o corpo do player*/
	initspritnavemae (corponavemae); 	/*Inicializa o corpo da nave mae*/

	t_listaTiros l_tiros,l_tirosA;
	t_listAliens l_aliens;
	t_listaBarreira l_barreira;

	inicializa_barreira (&l_barreira, telalinhas, telacolunas);
	inicializa_aliens (&l_aliens);
	initiros (&l_tiros);
	initiros (&l_tirosA);

	t_navemae navemae;			/*Coordenada nave mae*/
	int linha_alien = 7; 			/*Em qual linha, primeiramente, eu escrevo o alien*/
	int coluna_alien = 1; 			/*Em qual coluna, primeiramente,  eu escrevo o alien*/
	int player_linha = MINLINHAS-2;
	int player_coluna = MINCOLUNAS/2;
	int versao = 0; 			/*Versão que é para imprimir do alien*/
	int indo = 1; 				/*controla se o alien esta indo ou vindo*/
	int contiros = 0; 			/*quantidade de tiros na tela*/
	char key;
	int cnt = 0;
	int prdaliens = 20000;			/*Servira para controlar o periodo do alien*/ 
	int prdtiros = prdaliens/8;		/*periodo dos tiro (8x mais rapido que os aliens)*/
	int prdtirosA = 10000;
	int situacao;
	int contirosA = 0;      		/*quantida de tiros dos aliens*/ 
	int statusjogo = 0;
	int score = 0; 
	int chancenavemae;
	t_coord coordstr;			/*Ajudará no controle da impressao dos aliens*/

	t_controle linhasvivas, colunasvivas;
	initcontrole (&colunasvivas,COLUNASDALIENS-1,LINHASDALIENS);
	initcontrole (&linhasvivas,LINHASDALIENS-1,COLUNASDALIENS);
	
	navemae.coord.x = 0;
	navemae.coord.y = 0;
	navemae.status = MORRENDO;
	
	/*win = newwin (38,100,0,0);
	box(win, 0, 0);
	wrefresh(win);*/
	srand(time(NULL));

	while (l_aliens.tam != 0 && statusjogo != 1) {

		while (cnt <= PERIODODOJOGO && !ganhou(&l_aliens) && statusjogo != 1) {
			

			key = getch ();
		 	if (key == 'd') {
				if (player_coluna + 1 < MINCOLUNAS){
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
					instiroslista (&l_tiros,player_linha-1,player_coluna + 2);
				}
			}
			else if (key == 'q') {
				endwin();
				return 0;
			}

			if ((cnt % prdaliens/2) == 0 ) {
				
				chancenavemae = rand () % 9 + 1;

				if (chancenavemae >= 7 && navemae.status == 1) {
					prntnavemae (corponavemae,navemae);
					navemae.coord.y++;
					if (navemae.coord.y + LARGURANAVEMAE == MINCOLUNAS )
						navemae.status = 0;
				}
				else if (chancenavemae >= 7 && navemae.status == 0) {
					navemae.coord.x = 0;
					navemae.coord.y = 0;
					navemae.status = 1;
					prntnavemae (corponavemae,navemae);
				}

				if ((cnt % prdaliens) == 0) {
					admimpressao (&l_aliens,corposaliens,&indo,&versao,&linha_alien,&coluna_alien,&linhasvivas,&colunasvivas,telalinhas,telacolunas);
					if (dtctaclsalienbarreira (l_aliens,&l_barreira,linhasvivas,linha_alien,coluna_alien)) {
						prntbarreiras (&l_barreira);
					}
				}
			}
			else if (cnt == RESETACONTADOR)
				cnt = 0;
			
			if ((cnt % prdtiros) == 0) {
				
				t_tiro *tiro;
				tiro = l_tiros.ini->prox;
				while (tiro->prox != NULL) {

					situacao = detecta_tiro (&tiro->chave,&tiro->status,&l_aliens,&l_barreira,&l_tirosA,&navemae,linha_alien,coluna_alien);
					analizasituacao (situacao,&tiro->chave,&coordstr,&l_aliens,&l_barreira,&l_tirosA,navemae,corponavemae,corposaliens,&versao,&linha_alien,&coluna_alien,&contiros,&contirosA); 
					prntaliens (&l_aliens,corposaliens,&versao,&linha_alien,&coluna_alien);

					refresh ();
					if (situacao >= 1 && situacao <= 5) {
						if (situacao == 2) {
							vrfcextraliens (coordstr,&colunasvivas);	
							vrfcextraliens (coordstr,&linhasvivas);
							score = score + 10;
							/*mvprintw (0,telacolunas/2,"score: %d ", score);*/
						}
						else if (situacao == 3) {	
							score = score + 100;
							/*mvprintw (0,telacolunas/2,"score: %d ", score);*/
						}
						srchandrmtirolista (&l_tiros);
					}
					tiro = tiro->prox;
				}	
				prntiro (&l_tiros);
			}

			if ((cnt % prdtirosA) == 0){
				
				int i,ndoalien;
				t_coord coordbomba;


				ndoalien = rand () % l_aliens.tam;					 						/*sorteia um alien da lista para atirar;*/
				coordbomba = srchalien (ndoalien,&l_aliens,linha_alien,coluna_alien);
				if (contirosA < QNTDALIENTIROS ) {
						instiroslista (&l_tirosA,coordbomba.x,coordbomba.y);
						contirosA++;
				}

				t_tiro *bomba;
				bomba = l_tirosA.ini->prox;
				while (bomba->prox != NULL) {
					situacao = detecta_bomba (&bomba->chave,&bomba->status,&l_barreira, telalinhas, player_linha,player_coluna);
					analizasituacaoALIENS (situacao,&bomba->chave,&l_barreira,&statusjogo,&contirosA);

					if (situacao == 2 || situacao == 3)
						srchandrmtirolista (&l_tirosA);
					/*else if (situacao == 1) {
						usleep (100000);
						prntplayermorto (player_linha,player_coluna);
					}*/

					bomba = bomba->prox;
				}

				prntiroaliens (&l_tirosA);
			}
			prntplayer (corpoplayer,&player_linha,&player_coluna);
				
			/*refresh ();*/

			prntbarreiras (&l_barreira);
			cnt ++;

			refresh ();

		}	
	}
	/*For the time being, that's all folks*/

	endwin ();
	return 0;

}
