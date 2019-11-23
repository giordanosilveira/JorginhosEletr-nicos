/*realmente precisa uma matriz para os sprits ?*/
#include "lib_lista.h"
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
void initstructs (t_jogo *jogo, t_player *player, t_alien *aliens, t_alien *navemae, t_controle *row, t_controle *collum) {

    initjogo (jogo);
    initplayer (player);
    initalien (aliens,LINHALIEN,COLUNALIEN);
    initalien (navemae,LINHANAVEMAE,COLUNANAVEMAE);
    initcontrole (row,LINHALIEN - 1,COLUNALIEN);
    initcontrole (collum,COLUNALIEN - 1,LINHALIEN);

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
                coordx = (MAXLINHAS-10) + j;
                coordy = (MAXCOLUNAS/5)*i + k;
                insrlista (coordx,coordy,aliens);
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
}

/*Inicia a struct player*/
void initplayer (t_player *player) {
    player->rowplayer = MAXLINHAS - 2;
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
    strcpy (spritsaliens[7],ALIEN21);
    strcpy (spritsaliens[8],ALIEN21);
    strcpy (spritsaliens[9],ALIEN212);
    strcpy (spritsaliens[10],ALIEN222);
    strcpy (spritsaliens[11],ALIEN232);

    strcpy (spritsaliens[12],ALIEN31);
    strcpy (spritsaliens[13],ALIEN31);
    strcpy (spritsaliens[14],ALIEN31);
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

    if (! jogo->statusjogo)
        return 1;
    return 0;

}

int ganhou (t_lista *aliens) {

    if (lista_vazia (aliens))
        return 1;
    return 0;
}

int tecla (t_jogo *jogo, t_player *player, t_lista *tiros) {

    if (jogo->key == 'q') 
        return 0;
    else if (jogo->key == KEY_LEFT)
        moveplayer (jogo,player);
    else if (jogo->key == KEY_RIGHT)
        moveplayer (jogo,player);
    else if (jogo->key == ' ')
        addtirolista (jogo,tiros);

    return 1;

}

void moveplayer (t_jogo *jogo, t_player *player) {

    if (jogo->key == KEY_LEFT) {
    	if (player->collumplayer + 2 > LININIT)
        	player->collumplayer--;
    }
    else if (jogo->key == KEY_RIGHT) {
    	if (player->collumplayer + 7 < COLINIT)
        	player->rowplayer++;
    }
}

void addtirolista (t_jogo *jogo, t_player *player, t_lista *tiros) {
    if (jogo->contiros < TIROSPLAYER) {
        jogo->contiros++;
        insrlista (player->rowplayer - 1, player->collumplayer + 2,tiros);
    }
}

void admnavemae (t_navemae *navemae) {

    int chance;

    /*Rand chance*/

    /*Se a chance pode e nao esta printado, printa*/
    /*Senão continua printando*/
}
