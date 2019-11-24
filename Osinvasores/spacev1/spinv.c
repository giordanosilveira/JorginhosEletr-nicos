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
void initcontrole (t_controle *ctrl, int tam, int nelementos) {

	ctrl->fim = tam;
	ctrl->ini = 0;

	int i;
	for (i = 0; i <= ctrl->fim; i++) {
		ctrl->vetor[i].y = nelementos;
		ctrl->vetor[i].x = i;
	}
}
void initiros (t_listaTiros *l) {

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
				l->tam = 0;
			}
			else {
				free (fim);
				free (ini);
			}
		
		}
		else
			free (ini);
}
void instiroslista (t_listaTiros *l, int pos_x, int pos_y) {

	t_tiro *new;

	new = (t_tiro *)malloc(sizeof(t_tiro));
	if (new != NULL) {

		new->status = NPEGOU;

		new->chave.x = pos_x;
		new->chave.y = pos_y;

		l->tam++;

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
		
			l->tam = 0;

			l->ini = ini;
			l->fim = fim;

			l->ini->status = -1;
			l->fim->status = -1;

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
	
		l->tam++;

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

	int pos;
	t_alien *et;
	
	et = al->ini->prox;

	while (et->prox != NULL) {
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
		else if (et->status == MORRENDO) {
			mvprintw (*linha_alien+4*et->pos.x,*coluna_alien+7*et->pos.y,EXPLOSAOA1);
			mvprintw (*linha_alien+4*et->pos.x+1,*coluna_alien+7*et->pos.y,EXPLOSAOA2);
			mvprintw (*linha_alien+4*et->pos.x+2,*coluna_alien+7*et->pos.y,EXPLOSAOA3);
			
		}
		refresh();
		et = et->prox;
	}
}
void prntplayer (char **corpoP, int *linha_player, int *coluna_player) {
	/*Arrumar os rastro #nois*/
	mvprintw (*linha_player,*coluna_player+3,corpoP[0]);	
	mvprintw (*linha_player+1,*coluna_player-1,corpoP[1]);
}
void admimpressao (t_listAliens *l_aliens, char **corposaliens, int *indo, int *versao, int *linha_alien, int *coluna_alien, t_controle *linhasvivas, t_controle *colunasvivas, int *prdalien, int telalinhas, int telacolunas)
{

	t_alien *alien;
	int i=0;

	alien = l_aliens->ini->prox;

	clear ();
	
	if (*indo) {
		if (((colunasvivas->vetor[colunasvivas->fim].x*7) + 5) + *coluna_alien == MINCOLUNAS) {
			*coluna_alien = *coluna_alien - 1;
			*linha_alien = *linha_alien + 1;
			prntaliens (l_aliens,corposaliens,versao,linha_alien,coluna_alien);
			*prdalien = *prdalien - 100;
			*indo = 0;
		}
		else {
			*coluna_alien = *coluna_alien + 1;
			prntaliens (l_aliens,corposaliens,versao,linha_alien,coluna_alien);
		}
	}
	else {
		if (( *coluna_alien + colunasvivas->vetor[colunasvivas->ini].x*7 - 1 == 0)) {
			
			*coluna_alien = *coluna_alien + 1;
			*linha_alien = *linha_alien + 1;	
			prntaliens (l_aliens,corposaliens,versao,linha_alien,coluna_alien);
			*indo=1;	
			*prdalien = *prdalien - 100;
		}
		else {
			*coluna_alien = *coluna_alien - 1;
			prntaliens (l_aliens,corposaliens,versao,linha_alien,coluna_alien);
		}
	
	}
	*versao = (*versao + 1)%2;
}
void prntiro (t_listaTiros * l_tiros) { 

	t_tiro * tiro;

	if (l_tiros->tam != 0) {
		tiro = l_tiros->ini->prox;
		while (tiro->prox !=  NULL) {
			mvprintw (tiro->chave.x + 1,tiro->chave.y + 3," ");
			mvprintw (tiro->chave.x,tiro->chave.y + 3,"|");
			tiro = tiro->prox;
		}
	}
}
void initbarreira (t_listaBarreira *barreiras){

		t_barreira *ini, *fim;
		ini = (t_barreira*)malloc(sizeof(t_barreira));
		if (ini != NULL) {
			fim = (t_barreira *)malloc(sizeof(t_barreira));
			if (fim != NULL) {

				barreiras->ini = ini;
				barreiras->fim = fim;

				barreiras->ini->prox = fim;
				barreiras->ini->prev = NULL;

				barreiras->fim->prev = ini;
				barreiras->fim->prox = NULL;

				barreiras->tam = 0;
			}
			else {
				free (fim);
				free (ini);
			}
		
		}
		else
			free (ini);
}
void inspecabarlista (t_listaBarreira *barreira, int i, int j, int k, int telalinhas, int telacolunas) {

		t_barreira *peca;

		peca = (t_barreira *)malloc(sizeof(t_barreira));
		if (peca != NULL) {
	
			peca->status = VIVO;

			peca->chave.x = (MINLINHAS-10)+j;
			peca->chave.y = (MINCOLUNAS/5)*i + k;
	
			peca->prox = barreira->fim;
			peca->prev = barreira->fim->prev;

			barreira->fim->prev->prox = peca;
			barreira->fim->prev = peca;

			barreira->tam++;
	}
}
void inicializa_barreira (t_listaBarreira *barreiras, int telalinhas, int telacolunas) {

	initbarreira (barreiras);

	int i,j,k;
	for (i = 1; i <= 4; i++)
		for (j = 0; j < ALTURABARREIRA; j++) 
			for (k = 0; k < LARGURABARREIRA; k++) 
				inspecabarlista (barreiras,i,j,k,telalinhas,telacolunas);
}
void prntbarreiras (t_listaBarreira *barreira) {

	t_barreira *peca;

	peca = barreira->ini->prox;

	while (peca->prox != NULL) {
		if (peca->status == VIVO) {
				mvprintw (peca->chave.x, peca->chave.y, "M");
		}
		else {
			mvprintw (peca->chave.x-1, peca->chave.y-1,EXPLOSAOG1);
			mvprintw (peca->chave.x, peca->chave.y-1, EXPLOSAOG2);
			mvprintw (peca->chave.x+1, peca->chave.y-1, EXPLOSAOG3);
		}
		peca = peca->prox;
	}
}

void srchandrmtirolista (t_listaTiros *tiros) {

	t_tiro *tiro,*aux;
	tiro = tiros->ini->prox;
	while (tiro->prox != NULL && tiro->status != PEGOU)
		tiro = tiro->prox; 

	aux = tiro;
	tiro->prox->prev = tiro->prev;
	tiro->prev->prox = tiro->prox;
	tiros->tam--;
	free (aux);
}
void prntiroaliens (t_listaTiros * tirosA) {

	t_tiro * bomba;

	if (tirosA->tam != 0) {
		bomba = tirosA->ini->prox;
		while (bomba->prox !=  NULL) {
			mvprintw (bomba->chave.x - 1,bomba->chave.y," ");
			mvprintw (bomba->chave.x,bomba->chave.y,"$");
			bomba = bomba->prox;
		}
	}



} 
void srchanddstryalien (t_listAliens *aliens,t_coord *pos) {

	t_alien *alien,*aux;
	alien = aliens->ini->prox;
	while (alien->prox != NULL && alien->status != MORRENDO)
		alien = alien->prox; 

	pos->x = alien->pos.x;
	pos->y = alien->pos.y;

	aux = alien;
	alien->prox->prev = alien->prev;
	alien->prev->prox = alien->prox;
	aliens->tam--;
	free (aux);

}
void attbarreira (t_listaBarreira *barreiras) {

	t_barreira *bar,*aux;
	bar = barreiras->ini->prox;

	if (barreiras->tam != 0) {
		while	(bar->prox != barreiras->fim && bar->status != MORRENDO)
			bar = bar->prox;

		aux = bar;
		bar->prox->prev = bar->prev;
		bar->prev->prox = bar->prox;
		barreiras->tam--;
		free (aux);
	}
}
int detecta_bomba (t_coord *chave, int *status, t_listaBarreira *barreiras, int telalinha, int linha_player, int coluna_player ) {

	if (chave->x + 1 == MINLINHAS) {					/*Tiro chegou no final da tela*/
		*status = PEGOU;
		return 3;
	}

	t_barreira *bar;													/*Verifica se a bomba do alien pegou na barreira*/
	bar = barreiras->ini->prox;
	while (bar->prox != NULL) {
		if (chave->x + 1 == bar->chave.x && chave->y == bar->chave.y) {
			bar->status = MORRENDO;
			*status = PEGOU;
			return 2;
		}
		bar = bar->prox;
	}

	if (chave->x + 1 == linha_player && chave->y >= coluna_player + 3 && chave->y <= coluna_player + 8) { /*Verifica se a bomba pegou no jogador*/
		*status = PEGOU;
		return 1;
	}

	return 0;

}
int detecta_tiro (t_coord *chave, int *status, t_listAliens *aliens,t_listaBarreira *barreiras, t_listaTiros *tiros,t_navemae *navemae, int linha_alien, int coluna_alien) {

	
		if (chave->x - 1 == 0) {			/*tiro chegou no final da tela*/
			*status = PEGOU;
			return 5;
		}
	
		t_barreira *barreira;
		barreira = barreiras->ini->prox;
		while (barreira->prox != NULL) {
			if (chave->x-1 == barreira->chave.x && chave->y + 3 == barreira->chave.y) {
				barreira->status = MORRENDO;
				*status = PEGOU;
				return 1;
			}
			barreira = barreira->prox;
		}

		t_alien *alien;
		alien = aliens->ini->prox;
		while (alien->prox != NULL) {
			if ((chave->x - 1 == (alien->pos.x*4 + linha_alien)+2) && (chave->y + 3 >= (alien->pos.y*7 + coluna_alien)) && (chave->y + 3<= (alien->pos.y*7 + coluna_alien)+5)) {
				*status = PEGOU;
				alien->status = MORRENDO;
				return 2;
			}
			alien = alien->prox;
		
		}
		
		if (chave->x - 1 == navemae->coord.x + ALTURANAVEMAE-1 && chave->y + 3 <= navemae->coord.y + LARGURANAVEMAE - 1 && chave->y + 3 >= navemae->coord.y){
			navemae->status = MORRENDO;
			*status = PEGOU;
			return 3;
		}

		t_tiro *bomba;
		bomba = tiros->ini->prox;
		while (bomba->prox != NULL ){
			if (chave->x - 2 == bomba->chave.x && chave->y + 3 == bomba->chave.y) {
				*status = PEGOU;
				bomba->status = PEGOU;
				return 4;
			}
			bomba = bomba->prox;
		}

		return 0;

}
/*int detecta_tirosA ()*/

void analizasituacao (int situacao, t_coord *chave, t_coord *coordstr, t_listAliens *aliens, t_listaBarreira *barreiras, t_listaTiros * bombas, t_navemae navemae, char **corponavemae, char **corposA, int *versao, int *linha_alien, int *coluna_alien, int *contiros, int *contirosA) {
	t_tiro *bomba;

	switch (situacao) {
					
		case 0 :
		chave->x--;								/*caso que o tiro nao pega em nada*/		
		break;

		case 1 : 																	/*tiro pegou na barreira*/
		prntbarreiras (barreiras); 													/*printa a situação nova da barreira*/
		attbarreira (barreiras); 													/*atualiza a barreira*/
		*contiros = *contiros - 1;
		break;

		case 2 : 																	/*caso que o tiro pega em um alien*/
		prntaliens (aliens,corposA,versao,linha_alien,coluna_alien); 				/*printa os aliens direitos na tela*/
		srchanddstryalien (aliens,coordstr); 												/*acha o alien morto e remove o alien da lista*/
		*contiros = *contiros - 1;													/*diminui a qntd de tiros*/
		break;
								

		case 3 : 								/*pega na nave mae*/
		prntnavemae (corponavemae,navemae);
		*contiros = *contiros - 1;
		break;

		case 4 :								/*tiro pega no tiro do alien*/
		bomba = bombas->ini->prox;
		while (bomba->prox != NULL && bomba->status != PEGOU)
			bomba = bomba->prox;
		prntclstiro (&bomba->chave);
		srchandrmtirolista (bombas);
		*contirosA = *contirosA - 1;
		*contiros = *contiros - 1;
		break;

		default	: 								/*tiro chegou no final da tela;*/
		*contiros = *contiros - 1;						/*diminui a qntd de tiros*/
	}
}
t_coord srchalien (int ndoalien, t_listAliens *aliens, int linha_alien, int coluna_alien) {

	t_alien *aln;
	t_coord coord;
	aln = aliens->ini->prox;

	int i;
	for (i = 0; i < ndoalien; i++)
		aln = aln->prox;
	coord.x = (aln->pos.x*4 + linha_alien)+2;
	coord.y = ((aln->pos.y*7 + coluna_alien) + (aln->pos.y*7 + coluna_alien )+5)/2;

	return coord;
}
int perdeu (int statusjogo) {
	if (statusjogo)
		return 1;
	return 0;
}
int ganhou (t_listAliens *aliens) {

	if (aliens->tam == 0 )
		return 1;
	return 0; 

}
void analizasituacaoALIENS (int situacao, t_coord *chave, t_listaBarreira *barreiras, int *statusjogo, int *contirosA) {

	switch (situacao) {

		case 0 :										/*bomba não pega em nada*/
		chave->x++;
		break;

		case 1 :										/*tiro pega no player*/
		*statusjogo = 1;								/*Atualiza o jogo para "perdeu" */
		break;

		case 2 :										/*bomba pegou na barreira*/
		prntbarreiras (barreiras); 						/*printa a situação nova da barreira*/
		attbarreira (barreiras);
		*contirosA = *contirosA - 1;
		break;

		case 3 :										/*bomba chega ao final da tela*/
		*contirosA = *contirosA - 1;
		break;
	}
}
void prntplayermorto (int player_linha , int player_coluna) {
	mvprintw (player_linha,player_coluna,"EXPLOSAOP1");
	mvprintw (player_linha + 1,player_coluna,"EXPLOSAOP2");
}
void prntclstiro (t_coord *coord) {
	mvprintw (coord->x - 1,coord->y - 1,EXPLOSAOG1);
	mvprintw (coord->x,coord->y - 1,EXPLOSAOG2);
	mvprintw (coord->x + 1,coord->y - 1 ,EXPLOSAOG3);
}
void initspritnavemae (char **corponavemae) {
	strcpy (corponavemae[0],MAE1);
	strcpy (corponavemae[1],MAE2);
	strcpy (corponavemae[2],MAE3);
}
void prntnavemae (char **corponavemae, t_navemae navemae) {
	if (navemae.status == 1) {
		mvprintw (navemae.coord.x, navemae.coord.y, corponavemae[0]);
		mvprintw (navemae.coord.x + 1,navemae.coord.y,corponavemae[1]);
		mvprintw (navemae.coord.x + 2,navemae.coord.y,corponavemae[2]);
	}
	else {	
		mvprintw (navemae.coord.x, navemae.coord.y, EXPLOSAOG1);
		mvprintw (navemae.coord.x + 1,navemae.coord.y,EXPLOSAOG2);
		mvprintw (navemae.coord.x + 2,navemae.coord.y,EXPLOSAOG3);
	}
}
void vrfcextraliens (int coordy, t_controle * ctrl){
	
	ctrl->vetor[coordy].y--;
	
	int i;

	i = ctrl->fim;
	while (ctrl->vetor[i].y == 0) {
		i--;
		ctrl->fim--;
	}

	i = ctrl->ini;
	while (ctrl->vetor[i].y == 0) {
		i++;
		ctrl->ini++;
	}
}
int dtctaclsalienbarreira (t_listAliens aliens, t_listaBarreira *barreiras,t_controle linhasvivas, int linha_alien, int coluna_alien) {


	t_alien *alien;
	t_barreira *barreira;

	if ((linhasvivas.vetor[linhasvivas.fim].x*4 + 2) + linha_alien < MINLINHAS - 10)
		return 0;

	alien = aliens.ini->prox;

	while (alien->prox != aliens.fim) {

		barreira = barreiras->ini->prox;
		
		if (barreiras->fim != 0) {
			while (barreira != barreiras->fim) {
				if ((barreira->chave.x == (alien->pos.x*4 + linha_alien)+3)) {
					if ((barreira->chave.y == (alien->pos.y*7 + coluna_alien) - 1)  || barreira->chave.y == (alien->pos.y*7 + coluna_alien) + 1)			
						barreira->status = MORRENDO;
					else if ((barreira->chave.y == (alien->pos.y*7 + coluna_alien) + 6 ||  (barreira->chave.y == (alien->pos.y*7 + coluna_alien) + 5 ))) 
						barreira->status = MORRENDO;
				}
				barreira = barreira->prox;
			}
		}

		alien = alien->prox;

	}
	return 1;
	
}
int fimdalinha (t_controle ctrl, int linha_alien, int player_linha) {
	if ((ctrl.vetor[ctrl.fim].x*4 + 2) + linha_alien == player_linha)
		return 1; 
	return 0;
}
void destroi_listas (t_listaTiros *tiros, t_listaTiros *bombas, t_listAliens *aliens, t_listaBarreira *barreiras) {
	dstrlistatiro (tiros);
	dstrlistatiro (bombas);
	dstrlistaliens (aliens);
	dstrlistabarreira (barreiras);
}
void dstrlistatiro (t_listaTiros *t) {

	t_tiro *tiro;

	tiro = t->ini->prox;

	if (t->tam != 0) {
		while (tiro->prox != NULL){

			tiro=tiro->prox;
			free (tiro->prev);
			t->tam --;
		}
		free (t->ini);
		free (t->fim);
	}
}

void dstrlistabarreira (t_listaBarreira * t) {
	t_barreira *peca;

	peca = t->ini->prox;

	if (t->tam != 0) {
		while (peca->prox != NULL){

			peca=peca->prox;
			free (peca->prev);
			t->tam --;
		}
		free (t->ini);
		free (t->fim);
	}
}

void dstrlistaliens (t_listAliens *t) {
	t_alien *peca;

	peca = t->ini->prox;

	if (t->tam != 0) {
		while (peca->prox != NULL){

			peca=peca->prox;
			free (peca->prev);
			t->tam --;
		}
		free (t->ini);
		free (t->fim);
	}
}
void inicializa_listas (t_listaTiros *tiros, t_listaTiros *bombas, t_listAliens *aliens, t_listaBarreira *barreiras) {

	inicializa_aliens (aliens);
	inicializa_barreira (barreiras,0,0);
	initiros (tiros);
	initiros (bombas);
}
void increaseperiodo (int *prdA, int *cont) {
	if (*cont < 10000) {
		*prdA = *prdA - *cont;
		*cont = *cont + 1000;
	}
}
