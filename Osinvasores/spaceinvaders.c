#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "lib_lista.h"


int main () {

    initscr();                                                                      /* inicia a tela */
    cbreak();                                                                       /* desabilita o buffer de entrada */
    noecho();                                                                       /* não mostra os caracteres digitados */
    nodelay(stdscr, TRUE);                                                          /*faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);                                                           /* permite a leitura das setas */
    curs_set(FALSE);                                                                /* não mostra o cursor na tela */

    t_jogo jogo;
    t_player player;
    t_alien alien;
    t_alien navemae;
    t_controle row,collum;
    t_lista aliens;
    t_lista tiros;
    t_lista bombas;
    t_lista barreiras;    
    char **spritsaliens;

    initstructs (&jogo,&player,&alien,&navemae,&row,&collum);                      /*Inicializa as structs*/
    initlistas (&aliens,&tiros,&bombas,&barreiras);                                 /*Inicializa as listas*/

    spritsaliens = aloca_matriz (NSPRITSALIEN,LARGURALIENS);
    initspritsaliens (spritsaliens);                                                /*Inicializa os sprits dos aliens*/

    getmaxyx (stdscr,jogo.rowsscreen,jogo.collumscreen);                            /*Testa o tamanho da tela*/
    if (jogo.rowsscreen < MAXLINHAS || jogo.collumscreen < MAXCOLUNAS) {
        endwin();
        printf ("O terminal deve ter no mínimo 38 linhas por 100 colunas\n");
        return 1;
    } 

    borda (LININIT,COLINIT,MAXLINHAS-1,MAXCOLUNAS-1);                               /*Cria a borda do jogo*/
    srand(time(NULL));

    while (!perdeu(jogo)) {

        while (jogo.indice <= PERIODOJOGO && !ganhou (&aliens) && !perdeu (&jogo)) {
            
            clear ();

            jogo.key = getch ();
            
            /*Verifica qual tecla foi apertada*/
            if (!tecla (&jogo,&player,&tiros))
                return 0;

            /*Periodo de movimentação da navemae*/
            /*if ((jogo.indice % jogo.prdaliens/2) == 0) {
                admnavemae (&navemae);
            }*/

            /*Periodo de movimentação dos aliens*/
            if (jogo.indice % jogo.prdaliens == 0) {
                admaliens (&jogo,&alien,&aliens,&row,&collum);
            }

            /*periodo de movimentação dos tiros do player*/
            /*if ((jogo.indice % jogo.prdtiros) == 0) {
                admtiros (&jogo,&tiros,&bombas,&aliens,&barreiras);
            }*/

            /*periodo de movimentação das bombas dos aliens*/
            /*if ((jogo.indice % jogo.prdbombas) == 0) {
                admbombas (&jogo,&tiros,&bombas,&barreiras);
            }*/

            /*Reseta o laço mais interno*/
            if ((jogo.indice % RESETACONTADOR) == 0)
                rstcont (&jogo);
            
            prntplayer (player);
            prntbarreira (barreiras);

            jogo.indice++;    

            refresh ();

        }
        if (ganhou(&aliens)) {
            resetjogo (&t_jogo);
        }
        else {
            endwin ();
            printf ("Raul seixas\n");
        }

    }

    return 0;
}