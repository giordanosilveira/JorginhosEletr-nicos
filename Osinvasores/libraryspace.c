#include "lib_lista.h"
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
void initstructs (t_jogo *jogo, t_player *player, t_alien *aliens, t_alien *navemae, t_controle *row, t_controle *collum) {

    initjogo (jogo);
    initplayer (player);
    initalien (aliens,LINHALIEN,COLUNALIEN);
    initalien (navemae,LINHANAVEMAE,COLUNANAVEMAE);
    initcontrole (row,NLINHASALIENS - 1,NCOLUNASALIENS);
    initcontrole (collum,NCOLUNASALIENS - 1,NLINHASALIENS);

}

void initlistas (t_lista *aliens, t_lista *tiros, t_lista *bombas, t_lista *barreiras) {

    inicializa_lista (tiros);
    inicializa_lista (bombas);
    inicializa_lista (barreiras);
    inicializa_lista (aliens);

    int i,j,k;

    for (i = 0; i < NLINHASALIENS; i++)
        for (j = 0; j < NCOLUNASALIENS; j++)
            insrlista (i,j,aliens);

    int coordx, coordy;
    for (i = 1; i <= NBARREIRAS; i++) {
        for (j = 0; j < ALTURABARREIRA; j++) {
            for (k = 0; k < LARGURABARREIRA; k++) {
                coordx = (MAXLINHAS-10) + j;                        /*Conta para pegar a linha certa da barreira*/
                coordy = (MAXCOLUNAS/5)*i + k;                      /*Conta para peagr a coluna certa da barreira*/
                insrlista (coordx,coordy,barreiras);
            }
        }
    }

}

void initjogo (t_jogo *jogo) {
    jogo->contiros = 0;
    jogo->contbombas = 0;
    jogo->prdaliens = TIALIENS;
    jogo->prdtiros = TTIROS;
    jogo->prdbombas = TBOMBAS;
    jogo->indo = RIGHT;
    jogo->statusjogo = VIVO;
    jogo->indice = 0;
    jogo->amplificador = INITAPL;
    jogo->score = 0;   
}
/*Inicia a struct player*/
void initplayer (t_player *player) {
    player->rowplayer = MAXLINHAS - 3;
    player->collumplayer = MAXCOLUNAS/2;
}

/*Inicia a struct player*/
void initalien (t_alien *alien, int linha, int coluna) {
    alien->rowalien = linha;
    alien->collumalien = coluna;
    alien->versao = VERSAOINICIAL;
    alien->status = MORREU;
}

/*Inicia a struct controle*/
void initcontrole (t_controle *ctrl, int tam, int nelementos){
    
    ctrl->fim = tam;
    ctrl->ini = 0;

    int i;
    for (i = 0; i <= tam; i++) {
        ctrl->vetor[i].y = nelementos;
        ctrl->vetor[i].x = i;
    }
}

void initspritsaliens (char **spritsaliens) {

    strcpy (spritsaliens[0],ALIEN11);
    strcpy (spritsaliens[1],ALIEN12);
    strcpy (spritsaliens[2],ALIEN13);
    strcpy (spritsaliens[3],ALIEN112);
    strcpy (spritsaliens[4],ALIEN122);
    strcpy (spritsaliens[5],ALIEN132);

    strcpy (spritsaliens[6],ALIEN21);
    strcpy (spritsaliens[7],ALIEN22);
    strcpy (spritsaliens[8],ALIEN23);
    strcpy (spritsaliens[9],ALIEN212);
    strcpy (spritsaliens[10],ALIEN222);
    strcpy (spritsaliens[11],ALIEN232);

    strcpy (spritsaliens[12],ALIEN31);
    strcpy (spritsaliens[13],ALIEN32);
    strcpy (spritsaliens[14],ALIEN33);
    strcpy (spritsaliens[15],ALIEN312);
    strcpy (spritsaliens[16],ALIEN322);
    strcpy (spritsaliens[17],ALIEN332);

}

char** aloca_matriz (int altura, int largura) {

    int i;
    char **matriz;
    
    matriz = (char **)malloc(sizeof(char *)*altura);
    for (i = 0; i < altura; i++)
        matriz[i] = (char *)malloc(sizeof(char)*largura);
    
    return matriz;

}

void borda (int lininit, int colinit, int nlinhas, int ncolunas) {
    mvhline (lininit, colinit,  0,  ncolunas - colinit);
    mvhline (nlinhas, colinit,  0,  ncolunas - colinit);
    mvvline (lininit, colinit,  0,  nlinhas - lininit);
    mvvline (lininit, ncolunas, 0,  nlinhas - lininit);
    mvaddch (lininit, colinit, ACS_ULCORNER);
    mvaddch (nlinhas, colinit, ACS_LLCORNER);
    mvaddch (lininit, ncolunas, ACS_URCORNER);
    mvaddch (nlinhas, ncolunas, ACS_LRCORNER);
}

int perdeu (t_jogo * jogo) {

    if (jogo->statusjogo == MORREU)
        return 1;
    return 0;

}

int ganhou (t_lista *aliens) {

    if (lista_vazia (aliens))
        return 1;
    return 0;
}

void rstcont (t_jogo *jogo) {
    jogo->indice = 0;
}

int tecla (t_jogo *jogo, t_player *player, t_lista *tiros) {

    if (jogo->key == 'q') 
        return 0;
    else if (jogo->key == 'a')
        moveplayer (jogo,player);
    else if (jogo->key == 'd')
        moveplayer (jogo,player);
    else if (jogo->key == ' ')
        addtirolista (jogo,player,tiros);

    return 1;

}

void moveplayer (t_jogo *jogo, t_player *player) {

    if (jogo->key == 'a') {
    	if (player->collumplayer - 1 > COLINIT)
        	player->collumplayer--;
    }
    else if (jogo->key == 'd') {
    	if (player->collumplayer + 7 < MAXCOLUNAS)
        	player->collumplayer++;
    }
}

void addtirolista (t_jogo *jogo, t_player *player, t_lista *tiros) {
    if (jogo->contiros < TIROSPLAYER) {
        jogo->contiros++;
        insrlista (player->rowplayer - 1, player->collumplayer + 2,tiros);
    }
}

void nave_mae (t_alien *navemae) {

    int chance;
    
    chance = rand () % CHANCENAVEMAE + 1;
    if (chance >= CHANCENAVEMAE - 5) {
        navemaeaparece (navemae);
    }
    if (navemae->status == 1) {
        admnavemae (navemae);
    }
}

/*Faz a aparição da nave mae*/
void navemaeaparece (t_alien *navemae) {

    if (navemae->status == 0) {
        navemae->rowalien = 0;
        navemae->collumalien = 0;
        navemae->status = VIVO;
        prntnavemae (navemae);
    }
}

/*Admnista a impressão da nave mãe*/
void admnavemae (t_alien *navemae){

    prntnavemae (navemae);
    navemae->collumalien++;
    if (navemae->collumalien + TAMNAVEMAE == MAXCOLUNAS)
        navemae->status = MORREU;
}

/*Printa a nave mae*/
void prntnavemae (t_alien *navemae) {

    if (navemae->status == VIVO) {
        mvprintw (navemae->rowalien, navemae->collumalien, MAE1);
        mvprintw (navemae->rowalien + 1, navemae->collumalien, MAE2);
        mvprintw (navemae->rowalien + 2, navemae->collumalien, MAE3);
    }
    else {
        mvprintw (navemae->rowalien, navemae->collumalien, EXPLOSAOG1);
        mvprintw (navemae->rowalien + 1, navemae->collumalien, EXPLOSAOG2);
        mvprintw (navemae->rowalien + 2, navemae->collumalien, EXPLOSAOG3);
    }

}

void admaliens (t_jogo *jogo, t_alien *alien, t_lista *barreiras, t_lista *aliens, t_controle *row, t_controle *collum, char **spritsaliens) {

    clear ();
    int cont = 0, i;
    t_coord lixo;

    if (jogo->indo) {
        alienstoright (jogo,alien,aliens,row,collum,spritsaliens);
    }
    else {
        alienstoleft (jogo,alien,aliens,row,collum,spritsaliens);
    }
    alien->versao = (alien->versao +1) % 2;

    if (alienbarreira (aliens,barreiras,row,alien,&cont)) {
        for (i = 0 ; i <= cont; i++)
            srchandrmitemlista (&lixo,barreiras);
    }

}
int alienbarreira (t_lista *aliens, t_lista *barreiras, t_controle *row, t_alien *alien, int *cont) {

    if ((row->vetor[row->fim].x*4 + 2) + alien->rowalien < MAXLINHAS - 10)
        return 0;

    if (lista_vazia(aliens) || lista_vazia(barreiras))
        return 0;

    t_nodo *pecabar;

    pecabar = barreiras->ini->prox;

    while (pecabar->prox != NULL) {
          if (pecabar->status == VIVO) {
                if (pecabar->chave.x == row->vetor[row->fim].x * (4) + 2) {             /*Vericando se a linha do alien chegou na barreira*/
                        pecabar->status = MORREU;
                        *cont = *cont + 1;
                }
            }
            pecabar = pecabar->prox;
    }
    return 1;  
}

void nowayout (t_jogo *jogo, t_player *player, t_alien *alien, t_controle *row) {
    if (((row->vetor[row->fim].x * (3 + 1) + 2 ) + alien->rowalien == player->rowplayer))   /*Verificando se o alien chegou na coluna do player*/
        jogo->statusjogo = MORREU;
}

void alienstoright (t_jogo *jogo, t_alien *alien, t_lista *aliens, t_controle *row, t_controle *collum, char **spritsaliens) {

    if ((((collum->vetor[collum->fim].x *(SPACECALIENS + TAMALIEN)) + TAMALIEN) + alien->collumalien == MAXCOLUNAS)) {           /*Conta para pegar o final do*/
	alien->collumalien = alien->collumalien - 1;                                                                            /*alien e compara-lo com o tamanho maximo da tela*/
        alien->rowalien = alien->rowalien + 1;
        jogo->prdaliens = jogo->prdaliens - CTTDDMTMPALIENS;
        jogo->indo = 0;
        prntaliens (jogo,alien,aliens,spritsaliens);
    }
    else {
        alien->collumalien = alien->collumalien + 1;
        prntaliens (jogo,alien,aliens,spritsaliens);
    }

}

void alienstoleft (t_jogo *jogo, t_alien *alien, t_lista *aliens, t_controle *row, t_controle *collum, char **spritsaliens) {
    if ((alien->collumalien + collum->vetor[collum->ini].x *(SPACECALIENS + TAMALIEN) - 1 == COLINIT)) {                    /*Conta para medir a coluna do alien*/ 
        alien->collumalien = alien->collumalien + 1;                                                                        /*Em relação a parede inicial*/
        alien->rowalien = alien->rowalien + 1;
        jogo->indo = 1;
        jogo->prdaliens = jogo->prdaliens - CTTDDMTMPALIENS;
        prntaliens (jogo,alien,aliens,spritsaliens);
    }
    else {
        alien->collumalien = alien->collumalien - 1;
        prntaliens (jogo,alien,aliens,spritsaliens);
    }
}

void prntaliens (t_jogo *jogo, t_alien *alien, t_lista *aliens, char **spritsaliens) {
   
    /*coloca o incrementa atual*/

    int pos;
    t_nodo *et;

    
    if (! lista_vazia(aliens)){
    	
	et=aliens->ini->prox;

        while (et != aliens->fim)
        {
            pos = (et->chave.x + 1)/2;                                                            /*Conta para pegar o sprit certo do alien*/
		
            if (et->status == VIVO) {
                if (alien->versao) {
                    mvprintw (alien->rowalien + (ALTURALIEN + SPACELALIENS)*et->chave.x, alien->collumalien + (TAMALIEN + SPACECALIENS)*et->chave.y, spritsaliens[pos*6+3]);
                    mvprintw (alien->rowalien + (ALTURALIEN + SPACELALIENS)*et->chave.x+1, alien->collumalien + (TAMALIEN + SPACECALIENS)*et->chave.y, spritsaliens[pos*6+4]);
                    mvprintw (alien->rowalien + (ALTURALIEN + SPACELALIENS)*et->chave.x+2, alien->collumalien + (TAMALIEN + SPACECALIENS)*et->chave.y, spritsaliens[pos*6+5]);
                }
                else {
                    mvprintw (alien->rowalien + (ALTURALIEN + SPACELALIENS)*et->chave.x, alien->collumalien + (TAMALIEN + SPACECALIENS)*et->chave.y, spritsaliens[pos*6]);
                    mvprintw (alien->rowalien + (ALTURALIEN + SPACELALIENS)*et->chave.x+1, alien->collumalien + (TAMALIEN + SPACECALIENS)*et->chave.y, spritsaliens[pos*6+1]);
                    mvprintw (alien->rowalien + (ALTURALIEN + SPACELALIENS)*et->chave.x+2, alien->collumalien + (TAMALIEN + SPACECALIENS)*et->chave.y, spritsaliens[pos*6+2]);
                }
            }
            else if (et->status == MORREU) {
                    mvprintw (alien->rowalien + (ALTURALIEN + SPACELALIENS)*et->chave.x, alien->collumalien + (TAMALIEN + SPACECALIENS)*et->chave.y, EXPLOSAOA1);
                    mvprintw (alien->rowalien + (ALTURALIEN + SPACELALIENS)*et->chave.x+1, alien->collumalien + (TAMALIEN + SPACECALIENS)*et->chave.y, EXPLOSAOA2);
                    mvprintw (alien->rowalien + (ALTURALIEN + SPACELALIENS)*et->chave.x+2, alien->collumalien + (TAMALIEN + SPACECALIENS)*et->chave.y, EXPLOSAOA3);
            }
            et = et->prox;
        }
        refresh ();
    }
}

void prntplayer (t_player *player){
    mvprintw (player->rowplayer, player->collumplayer + 3, PLAYER11); 
    mvprintw (player->rowplayer + 1, player->collumplayer - 1, PLAYER12);
}

void prntbarreiras (t_lista *barreiras) {
    
    t_nodo *pecabar;

    if (! lista_vazia(barreiras)) {
    	pecabar = barreiras->ini->prox;
        while (pecabar != barreiras->fim)
        {
            if (pecabar->status == VIVO)
                mvprintw (pecabar->chave.x, pecabar->chave.y, "M");
            else {
                mvprintw (pecabar->chave.x - 1, pecabar->chave.y - 1, EXPLOSAOG1);
                mvprintw (pecabar->chave.x, pecabar->chave.y - 1, EXPLOSAOG2);
                mvprintw (pecabar->chave.x + 1, pecabar->chave.y - 1, EXPLOSAOG3);
            }
       	    pecabar = pecabar->prox;
       }    
   }
}

void admtiros (t_jogo *jogo, t_alien *alien, t_alien *navemae, t_controle *row, t_controle *collum, t_lista *aliens, t_lista *barreiras, t_lista *tiros, t_lista *bombas, char **spritesaliens) {

    t_coord aux;
    t_nodo *bala;
    if (!lista_vazia(tiros)) {
	bala = tiros->ini->prox;
        while (bala != tiros->fim)
        {
            jogo->situacao = detecta_colisao (alien,navemae,aliens,barreiras,bombas,&bala->chave,&bala->status);
            analizasituacao (jogo,alien,navemae,aliens,barreiras,bombas,&bala->chave,&aux,spritesaliens);
	        prntaliens (jogo,alien,aliens,spritesaliens);

            if (vrfcrmtiroslista(jogo,aux,row,collum))
                srchandrmitemlista (&aux,tiros);

	    bala = bala->prox;
        }
        prntiro (tiros); 
    }
}

int detecta_colisao (t_alien *alien, t_alien *navemae, t_lista *aliens, t_lista *barreiras, t_lista *bombas, t_coord *coord, int *status) {

    if (dtctcolisaotirobarreiras (barreiras,coord,status))
        return 0;

    if (dtctcolisaotiroaliens (aliens,coord,alien,status))
        return 1;

    if (dtctcolisaotirobombas(bombas,coord,status))
        return 2;

    if (dtctcolisaotironavemae (navemae,coord,status))
        return 3;

    if (nowayoutiros(coord,status))
        return 4;

    return 5;
}

/*detecta colisao entre o tiro e as barreiras*/
int dtctcolisaotirobarreiras (t_lista *barreiras, t_coord *chave, int *status){


    t_nodo *pecabar;
    if (! lista_vazia(barreiras)){
        pecabar = barreiras->ini->prox;
        while (pecabar != barreiras->fim)
        {
            if (chave->x - 1 == pecabar->chave.x && chave->y + 3 == pecabar->chave.y) { /*Se o tiro pegou na barreira*/
                pecabar->status = MORREU;
                *status = MORREU;
                return 1;
            }
            pecabar = pecabar->prox;
	}
    }
    return 0;
}

/*detecta colisao entre o tiro e os aliens*/
int dtctcolisaotiroaliens (t_lista *aliens, t_coord *chave, t_alien *alien, int *status) {
   
    t_nodo *ulib;

    if (! lista_vazia(aliens)){
    	ulib = aliens->ini->prox; 
        while (ulib != aliens->fim) { /*Esse if gigantesco só serve para ver se o tiro pegou no alien*/
            if (chave->x - 1 == (ulib->chave.x*(ALTURALIEN + SPACELALIENS)+alien->rowalien) + 2 && (chave->y + 3 >= ulib->chave.y*(TAMALIEN + SPACECALIENS)+alien->collumalien) && (chave->y + 3 <= (ulib->chave.y*(TAMALIEN + SPACECALIENS)+alien->collumalien) + 5)) {		
		ulib->status = MORREU;
                *status = MORREU;
                return 1;
            }
            ulib = ulib->prox;
	    }
    }
    return 0;
}

/*detecta colisao entre o tiro e as bombas*/
int dtctcolisaotirobombas (t_lista *bombas, t_coord *chave, int *status) {
    
    t_nodo *bomba;

    if (!lista_vazia(bombas)){
        bomba = bombas->ini->prox;    
        while (bomba != bombas->fim) {
            if (chave->x - 2 == bomba->chave.x && chave->y + 3== bomba->chave.y) {      /*Se o tiro pegou na bomba*/
                bomba->status = MORREU;
                *status = MORREU;
                return 1;
            }
            bomba = bomba->prox;
        }
    }
    return 0;
}

/*detecta colisao entre o tiro e a nave mae*/
int dtctcolisaotironavemae (t_alien *navemae, t_coord *chave, int *status) {
    
    /*Se o tiro pegou na nave mãe*/
    if (chave->x - 1 == navemae->rowalien + TAMNAVEMAE-1 && chave->y + 3 <= navemae->collumalien + TAMNAVEMAE - 1 && chave->y + 3 >= navemae->collumalien) {
        navemae->status = MORREU;
        *status = MORREU;
        return 1;
    }
    return 0;
}

int nowayoutiros (t_coord *coord, int *status) {
    if (coord->x - 1 == LININIT){                                                       /*Se o tiro chegou no fim da tela*/
    	*status = MORREU;
        return 1;
    }
    return 0;
}

void analizasituacao (t_jogo *jogo, t_alien *alien, t_alien *navemae, t_lista *aliens, t_lista *barreiras, t_lista *bombas, t_coord *chave, t_coord *aux, char **spritsaliens) {

    t_coord lixo;
    switch (jogo->situacao)
    {
        case 0:                                         /*Se o tiro pegou na barreira, remove a peca da lista*/
        prntbarreiras (barreiras);
        srchandrmitemlista (&lixo,barreiras);
        jogo->contiros--;
        break;

        case 1:                                         /*Se o tiro pegou no alien, remove o alien da lista*/
        prntaliens (jogo,alien,aliens,spritsaliens);
        srchandrmitemlista (aux,aliens);
        jogo->contiros--;
        break;

        case 2:
        prntbombas (bombas);                            /*Se o tiro pegou na bombas, remove o bomba da lista*/
        srchandrmitemlista (&lixo,bombas);
        jogo->contbombas--;
        jogo->contiros--;
        break;
    
        case 3:                                         /*Se o tiro pegou na nave mae, apaga a nave mãe*/
        prntnavemae (navemae);
	    navemae->status = MORREU;
        jogo->contiros--;
        break;
    
        case 4:                                         /*Se o tiro chegou ao fim da tela*/
        jogo->contiros--;
        break;
    
        default:                                        /*Se o tiro não pegou em nada*/
        chave->x--;
        break;
    }

}

void prntiro (t_lista *tiros) {

    if (inicializa_atual_inicio (tiros)) {
        while (tiros->atual != tiros->fim ) {
            if (tiros->atual->status) {
                mvprintw (tiros->atual->chave.x + 1, tiros->atual->chave.y + 3," ");
                mvprintw (tiros->atual->chave.x, tiros->atual->chave.y + 3,SPRTIRO1);
            }
            else {
                mvprintw (tiros->atual->chave.x - 1, tiros->atual->chave.y - 1,EXPLOSAOG1);
                mvprintw (tiros->atual->chave.x, tiros->atual->chave.y - 1,EXPLOSAOG2);
                mvprintw (tiros->atual->chave.x + 1, tiros->atual->chave.y - 1,EXPLOSAOG3);
            }
            tiros->atual = tiros->atual->prox;
        }
    }
}

void prntbombas (t_lista *bombas) {

    if (inicializa_atual_inicio (bombas)) {
        do
        {
            if (bombas->atual->status == VIVO) {
                mvprintw (bombas->atual->chave.x - 1, bombas->atual->chave.y, " ");
                mvprintw (bombas->atual->chave.x, bombas->atual->chave.y, "$");
            }
            else {
                mvprintw (bombas->atual->chave.x - 1, bombas->atual->chave.y - 1, EXPLOSAOG1);
                mvprintw (bombas->atual->chave.x, bombas->atual->chave.y - 1, EXPLOSAOG2);
                mvprintw (bombas->atual->chave.x + 1, bombas->atual->chave.y - 1, EXPLOSAOG3);
            }
        } while (incrementa_atual (bombas));
    }
}

int vrfcrmtiroslista (t_jogo *jogo, t_coord aux, t_controle *row, t_controle *collum) {

    if (jogo->situacao >= 0 && jogo->situacao <= 4) {
        if (jogo->situacao == 1 ){
            vrfcextaliens (aux.x,row);
            vrfcextaliens (aux.y,collum);
            jogo->score = jogo->score + 10;
        }
        else if (jogo->situacao == 3)
            jogo->score = jogo->score + 100;
        return 1;
    }
    return 0;
}

/*Todas essa contas são para ajudar na detecção do tiro e da borda*/
void vrfcextaliens (int coordy, t_controle *ctrl) {
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

void admbombas (t_jogo *jogo, t_lista *bombas, t_lista *barreiras, t_lista *aliens, t_player *player, t_alien *alien) {

    int ndoalien;
    t_coord coord; 
    if (! lista_vazia(aliens)) {                                                /*Escolhe um alien da lista para atirar*/
        ndoalien = rand() % aliens->tam;
        coord = srchalien (ndoalien,alien->rowalien,alien->collumalien,aliens); /*Devolve as coordenadas desse alien*/
        if (jogo->contbombas < BOMBASALIENS) {
            insrlista (coord.x,coord.y,bombas);
            jogo->contbombas++;
        }
    
        t_nodo *bomba;
        if (!lista_vazia(bombas)) {
            bomba = bombas->ini->prox;
            while (bomba != bombas->fim) {                                      /*Analiza se a bomba pegou em algo*/
                jogo->situacao = detecta_colisao_bombas (barreiras,player,jogo,&bomba->chave,&bomba->status);
                analizasituacaoaliens (jogo,&bomba->chave,barreiras);

                if (vrfcrmbombaslista (jogo))    
                    srchandrmitemlista (&coord,bombas);
                bomba = bomba->prox;
            }
        }
        prntbombas (bombas);
    }
}
int detecta_colisao_bombas (t_lista *barreiras, t_player *player, t_jogo *jogo, t_coord *coord, int *status) {

    if (dtctcolisaobombabarreira (barreiras,coord,status))
        return 0;

    if (dtctcolisaobombaplayer (player,coord,status))
        return 1;

    if (nowayoutbombas(coord,status))
        return 2;

    return 3;
}

int dtctcolisaobombabarreira (t_lista *barreiras, t_coord *chave, int *status) {
 
 t_nodo *pecabar;
    
    if (! lista_vazia(barreiras)){
        pecabar = barreiras->ini->prox;
        while (pecabar != barreiras->fim)
        {
            if (chave->x + 1 == pecabar->chave.x && chave->y == pecabar->chave.y) {             /*Se a bomba pegou na barreira*/
                pecabar->status = MORREU;
                *status = MORREU;
                return 1;
            }
            pecabar = pecabar->prox;
    	}
    }
    return 0;
}

int dtctcolisaobombaplayer (t_player *player, t_coord *chave, int *status) {

    /*Se a bomba pegou no player*/
    if (chave->x + 1 == player->rowplayer && chave->y >= player->collumplayer + 2 && chave->y <= player->collumplayer + 7) {
        *status = MORREU;
        return 1;
    }
    return 0;

}

int nowayoutbombas (t_coord *chave, int *status) {

    /*Se a bomba chegou ao fim da tela*/
    if (chave->x + 1 == MAXLINHAS) {
        *status = MORREU;
        return 1;
    }
    return 0;

}

void analizasituacaoaliens (t_jogo *jogo, t_coord *chave, t_lista *barreiras) {
    t_coord lixo;

    switch (jogo->situacao)
    {
        case 0:                                         /*Se a bomba pegou na barreira, remove a peca da lista*/
        prntbarreiras (barreiras);
        srchandrmitemlista (&lixo,barreiras);
        jogo->contbombas--;
        break;

        case 1:                                         /*Se a bomba pegou no player, acabou o jogo*/
        jogo->statusjogo = MORREU;
        jogo->contbombas--;
        break;

        case 2:                                         /*Se a bomba chegou ao fim da tela*/
        jogo->contbombas--;
        break;
    
        default :                                       /*Se a bomba não pegou em nada*/
        chave->x++;
        break;

    }
}

int vrfcrmbombaslista (t_jogo *jogo) {

    /*Verifica se a necessidade de remoção da bomba da lista*/
    if (jogo->situacao >= 0 && jogo->situacao <= 2)
        return 1;
    return 0;
}

void resetjogo (t_jogo *jogo, t_alien *alien) {

    jogo->contiros = 0;
    jogo->contbombas = 0;
    if (jogo->amplificador < MAXVELOCIDADE)
        jogo->prdaliens = TIALIENS - jogo->amplificador;
    jogo->amplificador = jogo->amplificador + INITAPL;
    jogo->indice = 0;
    jogo->statusjogo = VIVO;

    alien->collumalien = COLUNALIEN;
    alien->rowalien = LINHALIEN;
    alien->versao = VERSAOINICIAL;
    alien->status = MORREU;

}

void destroi_listas (t_lista *tiros, t_lista *bombas, t_lista *aliens, t_lista *barreiras) {

    destroi_lista (tiros);
    destroi_lista (bombas);
    destroi_lista (aliens);
    destroi_lista (barreiras);

}