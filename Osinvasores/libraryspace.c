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
                coordx = (MAXLINHAS-10) + j;
                coordy = (MAXCOLUNAS/5)*i + k;
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

void admaliens (t_jogo *jogo, t_alien *alien, t_lista *aliens, t_controle *row, t_controle *collum, char **spritsaliens) {

    clear ();
    if (jogo->indo) {
        alienstoright (jogo,alien,aliens,row,collum,spritsaliens);
    }
    else {
        alienstoleft (jogo,alien,aliens,row,collum,spritsaliens);
    }
    alien->versao = (alien->versao +1) % 2;

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
            else if (aliens->atual->status == MORREU) {
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
    mvprintw (0,60,"%d ", player->rowplayer);
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
                mvprintw (pecabar->chave.x - 1, pecabar->chave.y - 1, "M");
                mvprintw (pecabar->chave.x, pecabar->chave.y - 1, "M");
                mvprintw (pecabar->chave.x + 1, pecabar->chave.y - 1, "M");
            }
       	    pecabar = pecabar->prox;
       }    
   }
}

void admtiros (t_jogo *jogo, t_alien *alien, t_alien *navemae, t_controle *row, t_controle *collum, t_lista *aliens, t_lista *barreiras, t_lista *tiros, t_lista *bombas, char **spritesaliens) {

    t_coord aux;

    if (inicializa_atual_inicio (tiros)) {

        do
        {
            jogo->situacao = detecta_colisao (alien,navemae,aliens,barreiras,bombas,tiros->atual->chave,tiros->atual->status);
            analizasituacao (jogo,alien,navemae,aliens,barreiras,bombas,tiros->atual->chave,&aux,spritesaliens);

            if (vrfcrmtiroslista(jogo,aux,row,collum))
                srchandrmitemlista (tiros);

        } while (incrementa_atual(tiros));
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

    if (inicializa_atual_inicio(barreiras)){
        do
        {
            if (chave->x - 1 == barreiras->atual->chave.x && chave->y == barreiras->atual->chave.y) {
                barreiras->atual->status == MORREU;
                *status = MORREU;
                return 1;
            }
        } while (incrementa_atual(barreiras));
    }
    return 0;
}

/*detecta colisao entre o tiro e os aliens*/
int dtctcolisaotiroaliens (t_lista *aliens, t_coord *coord, t_alien*, int *status) {
    
    if (inicializa_atual_inicio(aliens)){
        do
        {
            if (chave->x - 1 == (aliens->atual->chave.x*(ALTURALIEN + SPACELALIENS)+alien->rowalien) + 2 && (chave->y >= aliens->atual->chave.y*(TAMALIEN + SPACELALIENS)+alien->collumalien) && (chave->y <= (aliens->atual->chave.y*(TAMALIEN + SPACECALIENS)+alien->collumalien) + 5)) {
                aliens->atual->status == MORREU;
                *status = MORREU;
                return 2;
            }
        } while (incrementa_atual(aliens));
    }
    return 0;
}

/*detecta colisao entre o tiro e as bombas*/
int dtctcolisaotirobombas (t_lista *bombas, t_coord *coord, int *status) {
    
    if (inicializa_atual_inicio(bombas)){
        do
        {
            if (chave->x - 2 == bombas->atual->chave.x && chave->y == bombas->atual->chave.y) {
                bombas->atual->status == MORREU;
                *status = MORREU;
                return 3;
            }
        } while (incrementa_atual(bombas));
    }
    return 0;
}

/*detecta colisao entre o tiro e a nave mae*/
int dtctcolisaotironavemae (t_alien *navemae, t_coord *coord, int *status) {
    
    if (chave->x - 1 == navemae->rowalien + TAMNAVEMAE-1 && chave->y <= navemae->collumalien.y + TAMNAVEMAE - 1 && chave->y >= navemae->collumalien) {
        navemae->status == MORREU;
        *status = MORREU;
        return 4;
    }
    return 0;
}

int nowayoutiros (t_coord *coord, int *status) {
    if (coord->x - 1 == LININIT)
        return 1
    return 0;
}

void analizasituacao (t_jogo *jogo, t_alien *alien, t_alien *navemae, t_lista *aliens, t_lista *barreiras, t_lista *bombas, t_coord *chave, t_coord *aux, char **spritsaliens) {

    t_coord *lixo;
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
        inicializa_atual_inicio (bombas);
        while (bombas->atual != bombas->fim && bombas->atual->status != MORREU)
            incrementa_atual (bombas);
        prntbombas (bombas->atual->chave);
        srchandrmitemlista (&lixo,bombas);
        jogo->contbombas--;
        jogo->contiros--;
        break;
    
        case 3:
        prntnavemae (navemae);
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

void prntiro (t_lista *tiros) {

    if (inicializa_atual_inicio (tiros)) {
        while (tiros->atual != tiros->fim ) {
            if (tiros->atual->status) {
                mvprintw (tiros->atual->chave.x + 1, tiros->atual->chave.y," ");
                mvprintw (tiros->atual->chave.x, tiros->atual->chave.y,SPRTIRO1);
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
        if (jogo->situacao == 2 ){
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

void vrfcextaliens (int coordy, t_coord *ctrl) {
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
