#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "libraryspace.h"
#include "lib_lista.h"

int main () {

    initscr();                                                                      /* inicia a tela */
    cbreak();                                                                       /* desabilita o buffer de entrada */
    noecho();                                                                       /* não mostra os caracteres digitados */
    nodelay(stdscr, TRUE);                                                          /* faz com que getch não aguarde a digitação */
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

    initstructs (&jogo,&player,&aliens,&navemae,&row,&collum);                      /*Inicializa as structs*/
    aloca_matriz (&spritsaliens,NSPRITSALIEN,LARGURALIENS);

    initspritsaliens (spritsaliens);

    getmaxyx (stdscr,jogo.rowsscreen,jogo.collumscreen);
    if (jogo.rowsscreen < MAXCOLUNAS || jogo.collumscreen < MAXLINHAS) {
        printf ("O terminal deve ter no mínimo 38 linhas por 100 colunas\n");
        endwin();
        return 0;
    } 

    initlistas (&aliens,&tiros,&bombas,&barreiras);                                 /*Inicializa as listas*/

    srand(time(NULL));

    while (!perdeu(jogo)) {
        while (jogo.indice <= PERIODOJOGO && !ganhou (&aliens) && !perdeu (&jogo)) {

        }
    }
}