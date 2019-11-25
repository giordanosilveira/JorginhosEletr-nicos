#include "lib_lista.h"
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

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
    if ((alien->collumalien + collum->vetor[collum->ini].x *(SPACECALIENS + TAMALIEN) - 1 == COLINIT)) {
        alien->collumalien = alien->collumalien + 1;
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

void analizasituacao (t_jogo *jogo, t_alien *alien, t_alien *navemae, t_lista *aliens, t_lista *barreiras, t_lista *bombas, t_coord *chave, t_coord *aux, char **spritsaliens) {

    t_coord lixo;
    switch (jogo->situacao)
    {
        case 0:
        prntbarreiras (barreiras);
        srchandrmitemlista (&lixo,barreiras);
        jogo->contiros--;
        break;

        case 1:
        prntaliens (jogo,alien,aliens,spritsaliens);
        srchandrmitemlista (aux,aliens);
        jogo->contiros--;
        break;

        case 2:
        prntbombas (bombas);
        srchandrmitemlista (&lixo,bombas);
        jogo->contbombas--;
        jogo->contiros--;
        break;
    
        case 3:
        prntnavemae (navemae);
	navemae->status = MORREU;
        jogo->contiros--;
        break;
    
        case 4:
        jogo->contiros--;
        break;
    
        default:
        chave->x--;
        break;
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
    if (! lista_vazia(aliens)) {
        ndoalien = rand() % aliens->tam;
        coord = srchalien (ndoalien,alien->rowalien,alien->collumalien,aliens);
        if (jogo->contbombas < BOMBASALIENS) {
            insrlista (coord.x,coord.y,bombas);
            jogo->contbombas++;
        }
    
        t_nodo *bomba;
        if (!lista_vazia(bombas)) {
            bomba = bombas->ini->prox;
            while (bomba != bombas->fim) {
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

void analizasituacaoaliens (t_jogo *jogo, t_coord *chave, t_lista *barreiras) {
    t_coord lixo;

    switch (jogo->situacao)
    {
        case 0:
        prntbarreiras (barreiras);
        srchandrmitemlista (&lixo,barreiras);
        jogo->contbombas--;
        break;

        case 1:
        jogo->statusjogo = MORREU;
        jogo->contbombas--;
        break;

        case 2:
        jogo->contbombas--;
        break;
    
        default :
        chave->x++;
        break;

    }
}

int vrfcrmbombaslista (t_jogo *jogo) {

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

