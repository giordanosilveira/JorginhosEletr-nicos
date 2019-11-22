/*realmente precisa uma matriz para os sprits ?*/

void initstructs (t_jogo *jogo, t_player *player, t_alien *aliens, t_controle *row, t_controle *collum) {

    initjogo (jogo);
    initplayer (player);
    initalien (aliens);
    initcontrole (row);
    initcontrole (collum);

}

void initjogo (t_jogo *jogo) {
    jogo->contiros = 0;
    jogo->contbombas = 0;
    jogo->prdaliens = PERIODOINICIAL;
    jogo->prdtiros = TTIROS;
    jogo->prdbombas = TBOMBAS;
    jogo->indo = RIGHT;
    jogo->statusjogo = VIVO;
    jogo->indice = 0;
    jogo->amplificador = INITAPL;
}

/*Inicia a struct player*/
void initplayer (t_player *) {

}

/*Inicia a struct player*/
void initalien (t_alien *) {

}

/*Inicia a struct controle*/
void initcontrole (t_controle *){
    
}
