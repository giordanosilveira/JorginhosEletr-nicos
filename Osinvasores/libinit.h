#include "lib_lista.h"

/*Inicializa todas as structs*/
void initstructs (t_jogo *, t_player *, t_alien *, t_alien *, t_controle *, t_controle *);

/*Inicializa as listas*/
void initlistas (t_lista *, t_lista *, t_lista *, t_lista *);

/*Inicia a struct jogo*/
void initjogo (t_jogo *);

/*Inicia a struct player*/
void initplayer (t_player *);

/*Inicia a struct player*/
void initalien (t_alien *, int, int);

/*Inicia a struct controle*/
void initcontrole (t_controle *, int, int);

/*Inicializa os sprits dos aliens*/
void initspritsaliens (char **);

/*Aloca matriz*/
char ** aloca_matriz (int, int);


