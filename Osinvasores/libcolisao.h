#include "lib_lista.h"

/*Verifica se os aliens pegaram na barreiras*/
int alienbarreira (t_lista *, t_lista *, t_controle *, t_alien *, int *);

/*Verifica se os aliens chegar na linha do player*/
void nowayout (t_jogo *, t_player *, t_alien *, t_controle *);

/*Detecta se o tiro pegou em algo*/
int detecta_colisao (t_alien *, t_alien * , t_lista * , t_lista *,t_lista*, t_coord *, int *);

/*detecta colisao entre o tiro e as barreiras*/
int dtctcolisaotirobarreiras (t_lista *, t_coord *, int *);

/*detecta colisao entre o tiro e os aliens*/
int dtctcolisaotiroaliens (t_lista *, t_coord *,t_alien *, int *);

/*detecta colisao entre o tiro e as bombas*/
int dtctcolisaotirobombas (t_lista *, t_coord *, int *);

/*detecta colisao entre o tiro e a nave mae*/
int dtctcolisaotironavemae (t_alien *, t_coord *, int *);

/*Verifica se o tiro chegou no início da tela*/
int nowayoutiros (t_coord *, int *);

/*Detecta a colisao entre as bombas e algo*/
int detecta_colisao_bombas (t_lista *, t_player *, t_jogo *, t_coord *, int *);

/*Detecta a colisa entre a bomba e a barreira*/
int dtctcolisaobombabarreira (t_lista *, t_coord *, int *);

/*Detecta a colisao entre a bomba e o player*/
int dtctcolisaobombaplayer (t_player *, t_coord *,int *);

/*Detecta a colisao entre as bombas e o fim da tela*/
int nowayoutbombas (t_coord *, int *);

