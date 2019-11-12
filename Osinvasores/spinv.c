#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
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

void initspritplayer (char ** c_player) {
	strcpy (c_player[0],PLAYER11);
	strcpy (c_player[1],PLAYER12);	
}

void initiros (t_listaTiro *l) {

		t_tiro *ini, *fim;
		ini = (t_tiro *)malloc(sizeof(t_tiro));
		if (ini != NULL) {
			fim = (t_tiro *)malloc(sizeof(t_tiro));
			if (fim != NULL) {

				l->ini = ini;
				l->fim = fim;

				ini->prox = fim;
				ini->prev = NULL;

				fim->prev = ini;
				fim->prox = NULL;

				l->atual = NULL;
				l->tamanho = 0;
			}
			else {
				free (fim);
				free (ini);
			}
		
		}
		else
			free (ini);
}
void instiroslista (t_listaTiros *l) {

	t_tiro *new;

	new = (t_tiro *)malloc(sizeof(t_tiro))
	if (new != NULL) {

		new->chave.x = pos_x;
		new->chave.y = pos_y;

		l->tamanho++;

		new->prox = l->fim;
		new->prev = l->fim->prev;

		new->prev->prox = new;
		l->fim->prev = new;
	}
}
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

void insalienslista (t_listAliens *l, int x, int y) {

	t_alien *et;

	et = (t_alien *)malloc(sizeof(t_alien));
	if (et != NULL) {
	
		et->status = VIVO;
	
		et->pos.x = x;
		et->pos.y = y;

		et->prox = l->fim;
		et->prev = l->fim->prev;

		l->fim->prev->prox = et;
		l->fim->prev = et;
	}
}
void inicializa_aliens (t_listAliens *aliens) {
	
	initaliens (aliens);

	int i,j;

	for (i = 0; i < LINHASDALIENS; i++) {
		for (j = 0; j < COLUNASDALIENS; j++)
			insalienslista (aliens,i,j);
	printf ("\n");
	}
}
void prntaliens (t_listAliens *al,char **corposA,int *versao, int *linha_alien, int *coluna_alien) {

	int k,pos;
	t_alien *et;
	
	et = al->ini->prox;
	k = 0;

	while (k < QNTET) {

		pos = (et->pos.x + 1)/2;		/*essa conta serve para pegar o sprit desejado do alien*/
		if (et->status == VIVO) {
			if (*versao) { /*se a versao do alien for 1 ele entra aqui*/ 
				mvprintw (*linha_alien+4*et->pos.x,*coluna_alien+7*et->pos.y,corposA[pos*6+3]);	
				mvprintw (*linha_alien+4*et->pos.x+1,*coluna_alien+7*et->pos.y,corposA[pos*6+4]);
				mvprintw (*linha_alien+4*et->pos.x+2,*coluna_alien+7*et->pos.y,corposA[pos*6+5]);
			}
			else {
				
				mvprintw (*linha_alien+4*et->pos.x,*coluna_alien+7*et->pos.y,corposA[pos*6]);
				mvprintw (*linha_alien+4*et->pos.x+1,*coluna_alien+7*et->pos.y,corposA[pos*6+1]);
				mvprintw (*linha_alien+4*et->pos.x+2,*coluna_alien+7*et->pos.y,corposA[pos*6+2]);
			}
	
		}
		et = et->prox;
		k++;
	}
}
void prntplayer (char **corpoP, int *linha_player, int *coluna_player) {
	mvprintw (*linha_player,*coluna_player,corpoP[0]);	
	mvprintw (*linha_player+1,*coluna_player-1,corpoP[1]);
}
void inicializa_controle (t_controle *linhAliens, t_controle *colunAliens) {

	int i;
	
	linhAliens->tam = 5;
	colunAliens->tam = 11;

	linhAliens->vetor = (int *)malloc(sizeof(int)*linhAliens->tam);
	colunAliens->vetor = (int *)malloc(sizeof(int)*colunAliens->tam);

	if (linhAliens == NULL || colunAliens == NULL) {
		free (linhAliens);
		free (colunAliens);
	}
	else {
		for (i = 0; i < colunAliens->tam; i++) {
			if (i < 5)
				linhAliens->vetor[i] = i;
			colunAliens->vetor[i] = i;
		}
	}
}
void admimpressao (t_listAliens *l_aliens, char **corposaliens, int *indo, int *versao, int *linha_alien, int *coluna_alien, t_controle *linhasvivas, t_controle *colunasvivas,int telalinhas, int telacolunas)
{

	t_alien *alien;
	int i=0;

	alien = l_aliens->ini->prox;

	if (*indo) {
		if (11*7 + *coluna_alien == telacolunas) {
			*coluna_alien = *coluna_alien - 1;
			*linha_alien = *linha_alien + 1;
			prntaliens (l_aliens,corposaliens,versao,linha_alien,coluna_alien);
			*indo = 0;
		}
		else {
			*coluna_alien = *coluna_alien + 1;
			prntaliens (l_aliens,corposaliens,versao,linha_alien,coluna_alien);
		}
	}
	else {
		if (*coluna_alien-1 == 0) {
			*coluna_alien = *coluna_alien + 1;
			*linha_alien = *linha_alien + 1;	
			prntaliens (l_aliens,corposaliens,versao,linha_alien,coluna_alien);
			*indo=1;
		}
		else {
			*coluna_alien = *coluna_alien - 1;
			prntaliens (l_aliens,corposaliens,versao,linha_alien,coluna_alien);
		}
	
	}
	*versao = (*versao + 1)%2;
}
void prntiro (char key, t_tiro * int contiros, ) {

	if (key != ' ')
		return;
	
	mvprintw (*linha_player-1,coluna_player+3,"|");

}
