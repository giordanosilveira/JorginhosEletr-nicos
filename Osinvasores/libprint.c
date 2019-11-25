#include "libprint.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

