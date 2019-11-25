#include "libcolisao.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int alienbarreira (t_lista *aliens, t_lista *barreiras, t_controle *row, t_alien *alien, int *cont) {

    if ((row->vetor[row->fim].x*4 + 2) + alien->rowalien < MAXLINHAS - 10)
        return 0;

    if (lista_vazia(aliens) || lista_vazia(barreiras))
        return 0;

    t_nodo *pecabar;

    pecabar = barreiras->ini->prox;

    while (pecabar->prox != NULL) {
          if (pecabar->status == VIVO) {
                if (pecabar->chave.x == row->vetor[row->fim].x * (4) + 2) {
                        pecabar->status = MORREU;
                        *cont = *cont + 1;
                }
            }
            pecabar = pecabar->prox;
    }
    return 1;  
}

void nowayout (t_jogo *jogo, t_player *player, t_alien *alien, t_controle *row) {
    if (((row->vetor[row->fim].x * (3 + 1) + 2 ) + alien->rowalien == player->rowplayer))
        jogo->statusjogo = MORREU;
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
            if (chave->x - 1 == pecabar->chave.x && chave->y + 3 == pecabar->chave.y) {
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
        while (ulib != aliens->fim) {
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
            if (chave->x - 2 == bomba->chave.x && chave->y + 3== bomba->chave.y) {
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
    
    if (chave->x - 1 == navemae->rowalien + TAMNAVEMAE-1 && chave->y + 3 <= navemae->collumalien + TAMNAVEMAE - 1 && chave->y + 3 >= navemae->collumalien) {
        navemae->status = MORREU;
        *status = MORREU;
        return 1;
    }
    return 0;
}

int nowayoutiros (t_coord *coord, int *status) {
    if (coord->x - 1 == LININIT){
    	*status = MORREU;
        return 1;
    }
    return 0;
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
            if (chave->x + 1 == pecabar->chave.x && chave->y == pecabar->chave.y) {
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

    if (chave->x + 1 == player->rowplayer && chave->y >= player->collumplayer + 2 && chave->y <= player->collumplayer + 7) {
        *status = MORREU;
        return 1;
    }
    return 0;

}

int nowayoutbombas (t_coord *chave, int *status) {

    if (chave->x + 1 == MAXLINHAS) {
        *status = MORREU;
        return 1;
    }
    return 0;

}
