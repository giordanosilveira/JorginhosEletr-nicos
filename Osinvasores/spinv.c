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
		else if (et->status == MORRENDO)
		{
			mvprintw (*linha_alien+4*et->pos.x+2,*coluna_alien+7*et->pos.y,EXPLOSAOA1);
			mvprintw (*linha_alien+4*et->pos.x+2,*coluna_alien+7*et->pos.y,EXPLOSAOA2);
			mvprintw (*linha_alien+4*et->pos.x+2,*coluna_alien+7*et->pos.y,EXPLOSAOA3);	
		}
		refresh();
		et = et->prox;
	}
}
void prntplayer (char **corpoP, int *linha_player, int *coluna_player) {
	/*Arrumar os rastro #nois*/
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

	clear ();
	
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
void prntiro (t_listaTiros * l_tiros, int contiros) { 

	t_tiro * tiro;

	if (l_tiros->tam != 0) {
		tiro = l_tiros->ini->prox;
		while (tiro->prox !=  NULL) {
			mvprintw (tiro->chave.x + 1,tiro->chave.y," ");
			mvprintw (tiro->chave.x,tiro->chave.y,"|");
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

			peca->chave.x = (telalinhas-10)+j;
			peca->chave.y = (telacolunas/5)*i + k;
	
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
	free (aux);
}
/*void prntiroaliens () */
void srchanddstryalien (t_listAliens *aliens) {

	t_alien *alien,*aux;
	alien = aliens->ini->prox;
	while (alien->prox != NULL && alien->status != MORRENDO)
		alien = alien->prox; 

	aux = alien;
	alien->prox->prev = alien->prev;
	alien->prev->prox = alien->prox;
	free (aux);

}
/*void attbarreira ()*/
int detecta_tiro (t_coord *chave, int *status, t_listAliens *aliens, int linha_alien, int coluna_alien) {

	
		if (chave->x - 1 == 0) {			/*tiro chegou no final da tela*/
			*status = PEGOU;
			return 5;
		}
	
		t_alien *alien;
		alien = aliens->ini->prox;
		while (alien->prox != NULL) {
			if ((alien->pos.x + linha_alien <= chave->x) && (chave->x <= alien->pos.x + linha_alien + 3) && (chave->y <= alien->pos.y + coluna_alien + TAMALIEN -1) && (chave->y >= alien->pos.y + coluna_alien)) {
				*status = PEGOU;
				alien->status = MORRENDO;
				return 1;
			}
			alien = alien->prox;
		
		}
	return 0;

}
/*void rddtirosaliens () */
/*int detecta_tirosA ()*/

void analizasituacao (int situacao, t_coord *chave, t_listAliens *aliens,char **corposA, int *versao, int *linha_alien, int *coluna_alien, int *contiros) {

	switch (situacao) {
					
		case 0 :
		chave->x--;				/*caso que o tiro nao pega em nada*/		
		break;

		case 1 : 				/*caso que o tiro pega em um alien*/
		prntaliens (aliens,corposA,versao,linha_alien,coluna_alien); 			/*printa os aliens direitos na tela*/
		srchanddstryalien (aliens); 	/*acha o alien morto e remove o alien da lista*/
		*contiros = *contiros - 1;	/*diminui a qntd de tiros*/
		break;
								
		/*case 2 : 				tiro pegou na barreira
		attbarreira (); 		atualiza os status da barreira
		prntbarreiras (); 		printa a situação nova da barreira 
		break;*/

		/*case 3 : 				pega na nave mae
		break;*/

		/*case 4 :				tiro pega no tiro do alien
		break;*/

		default	: 				/*tiro chegou no final da tela;*/
		*contiros = *contiros - 1;	/*diminui a qntd de tiros*/
		}
}
/*void analizasituacaoALIENS () {}*/
