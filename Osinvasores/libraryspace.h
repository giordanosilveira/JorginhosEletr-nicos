
/*player*/
#define TIROSPLAYER 8
#define PLAYER11 " / \\ "
#define PLAYER12 "   /MMMMM\\   "

/*Sprits Alien 1*/
#define ALIEN11 "/T-T\\"
#define ALIEN12 "()-()"
#define ALIEN13 "|W-W|"
#define ALIEN112 "/*-*\\"
#define ALIEN122 "/(|)\\"
#define ALIEN132 "|W-W|"

/*Sprits Alien 2*/
#define ALIEN21 "(O@O)"
#define ALIEN22 "}MOM{"
#define ALIEN23 "().()"
#define ALIEN212 "(*-*)"
#define ALIEN222 "{MAM}"
#define ALIEN232 "()_()"

/*Sprits Alien 3*/
#define ALIEN31 "(O.O)"
#define ALIEN32 "|/*\\|"
#define ALIEN33 ")WTW("
#define ALIEN312 "(O.O)"
#define ALIEN322 "/|*|\\"
#define ALIEN332 "(WTW)"

/*Sprit Nave mãe*/
#define MAE1 " ^ "
#define MAE2 "MoM"
#define MAE3 "/-\\"

/*sprit explosao player*/
#define EXPLOSAOP1 "\\\\-O-//"
#define EXPLOSAOP2 "WAS TED"

/*Sprit explosão alien*/
#define EXPLOSAOA1 "\\\\  //"
#define EXPLOSAOA2 "-|10|-"
#define EXPLOSAOA3 "//  \\\\"

/*sprit explosão geral*/
#define EXPLOSAOG1 "\\ /"
#define EXPLOSAOG2 "-o-"
#define EXPLOSAOG3 "/ \\"

/*Tamanho da tela*/
#define LININIT 0
#define COLINIT 0
#define MAXLINHAS 38
#define MAXCOLUNAS 100

/*Tudo o que tem haver com as barreiras*/
#define NBARREIRAS 4
#define ALTURABARREIRA 3
#define LARGURABARREIRA 8

/*Controla o perido do jogo*/
#define PERIODOJOGO 40000
#define RESETACONTADOR 39999
#define TIALIENS 20000
#define TNAVEMAE 10000
#define CTTDDMTMPALIENS 100                         /*ConsTanTe de DiMinuição do (TM)Perido dos Aliens*/

/*Tudo o que tem haver com os aliens*/
#define BOMBASALIENS 6
#define TAMNAVEMAE 3
#define CHANCENAVEMAE
#define TAMALIEN 5
#define ALTURALIEN 3
#define SPACECALIENS 2
#define SPACELALIENS 1
#define VERSAOINICIAL 0
#define LINHALIEN 7
#define COLUNALIEN 1
#define LINHANAVEMAE 0
#define COLUNANAVEMAE 0
#define NLINHASALIENS 5
#define NCOLUNASALIENS 11
#define NSPRITSALIEN 18
#define LARGURALIENS 6

/*Tudo o que tem haver com os tiros*/
#define TTIROS 2500
#define SPRTIRO1 "|"
#define SPRTIRO2 "-"

/*Tudo o que tem haver com as bombas*/
#define TBOMBAS 10000
#define SPRTBOMBA1 "$"
#define SPRTBOMBA2 "!"

/*Status do jogo*/
#define MORREU 0
#define VIVO 1
#define GANHOU 1
#define PERDEU 0

/*Inicio do jogo->amplificador*/
#define INITAPL 1000

/*Movimentação*/
#define UP 1
#define DOWN -1
#define LEFT -1
#define RIGHT 1

struct t_jogo {
    int rowsscreen, collumscreen;                               /*linha e coluna da tela*/
    int contiros, contbombas;                                   /*contador dos tiros e das bombas*/
	int prdaliens, prdtiros, prdbombas;                         /*periodo do alien, tiro do player e bombas dos aliens*/
    int situacao;                                               /*Vai ajudar na detecção de tiros e bombas*/
    int indo;                                                   /*controla a movimentação dos aliens*/
    int statusjogo;                                             /*Verifica se o jogador venceu ou perdeu o jogo*/
    int score;                                                  /*pontuação do player*/
    int indice;                                                 /*indice do while pricipal*/
    int amplificador;                                           /*aumentara a velocidade dos aliens*/
    char key;
};
typedef struct t_jogo t_jogo;                                   /*Principais variaveis do jogo*/

struct t_alien {
    int rowalien,collumalien;                                  /*Linha e coluna aonde começam os aliens*/
    int versao;                                                 /*Qual versão é para printar do alien*/
    int status;                                                 /*servirá apenas para a nave mãe*/
};
typedef struct t_alien t_alien;

struct t_player {
    int rowplayer, collumplayer;                                
};
typedef struct t_player t_player;

struct t_coord {
    int x,y; 
};
typedef struct t_coord t_coord;

struct t_controle {
	int fim;
	int ini;
	t_coord vetor[11];
};
typedef struct t_controle t_controle;                                  /*Struct que servirá para o controle da movimentção dos aliens*/

struct t_nodo {
    int status;
    t_coord chave;
    struct t_nodo *prev;
    struct t_nodo *prox;
};
typedef struct t_nodo t_nodo;                                   /*Nodo que contem todas as irformações que precisa para uma lista generica*/

struct t_lista {
    int tam;
    t_nodo *ini;
    t_nodo *fim;
    t_nodo *atual;
};
typedef struct t_lista t_lista;                                 /*Lista genérica*/

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

/*Verifica se o jogador perdeu o jogo*/
int perdeu (t_jogo *);

/*Verifca se o jogador ganhou*/
int ganhou (t_lista *);

/*Decide o destino de acordo com a tecla apertada*/
int tecla (t_jogo *, t_player *, t_lista *);

/*Move o jogador*/
void moveplayer (t_jogo *, t_player *);

/*Adiciona, quando possível, um tiro na lista*/
void addtirolista (t_jogo *, t_player *, t_lista *);

/*Aloca matriz*/
char ** aloca_matriz (int, int);

/*Insere a posição primeiramente nas lista*/
void insrprimeiro (t_lista *, int, int, int);

/*Faz a borda do jogo*/
void borda (int, int , int , int);

/*Reseta o contador*/
void rstcont (t_jogo *);

/*Administra os aliens*/
void admaliens (t_jogo *, t_alien *, t_lista *, t_controle *, t_controle *, char **);

/*Administra a impressao aliens*/
void admimpressao (t_jogo *, t_alien *, t_lista *, t_controle  *, t_controle *, char **);

/*impressão dos aliens para a esquerda*/
void alienstoleft (t_jogo *, t_alien *, t_lista *, t_controle *, t_controle *, char **);

/*Impressão dos aliens para a direita*/
void alienstoright (t_jogo *, t_alien *, t_lista *, t_controle *, t_controle *, char **);

/*printa os aliens*/
void prntaliens (t_jogo *, t_alien *, t_lista *, char **);

/*Administra a nave mãe*/
void nave_mae (t_alien *);

/*Faz a aparição da nave mae*/
void navemaeaparece (t_alien *);

/*Admnista a impressão da nave mãe*/
void admnavemae (t_alien *);

/*Printa a nave mae*/
void prntnavemae (t_alien *);

/*Printa o player*/
void prntplayer (t_player *);

/*Printa a barreira*/
void prntbarreiras (t_lista *);

/*Admnistra os tiros do player*/
void admtiros (t_jogo *, t_alien *, t_alien *, t_controle *, t_controle *, t_lista *, t_lista *, t_lista *, t_lista *,char **);

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

/*De acordo com a situação escolhe uma decisão para ser tomada*/
void analizasituacao (t_jogo *, t_alien *, t_alien *, t_lista *, t_lista *, t_lista * ,t_coord *, t_coord *, char **);

/*printa os tiros*/
void prntiro (t_lista *);

/*printa as bombas e a colisao entre elas e os tiros */
void prntbombas (t_lista *);

/*Verifica se a necessida de remover o tiro da lista e atualiza as colunas e as linhas dos aliens*/
int vrfcrmtiroslista (t_jogo *,t_coord , t_controle *, t_controle *);

/*Atualiza as linha e as colunas dos aliens*/
void vrfcextaliens (int , t_controle *);

/*Administra as bombas dos aliens*/
void admbombas (t_jogo *, t_lista *, t_lista *, t_lista *, t_player *, t_alien *);

/*Detecta a colisao entre as bombas e algo*/
int detecta_colisao_bombas (t_lista *, t_player *, t_jogo *, t_coord *, int *);

/*Detecta a colisa entre a bomba e a barreira*/
int dtctcolisaobombabarreira (t_lista *, t_coord *, int *);

/*Detecta a colisao entre a bomba e o player*/
int dtctcolisaobombaplayer (t_player *, t_coord *,int *);

/*Detecta a colisao entre as bombas e o fim da tela*/
int nowayoutbombas (t_coord *, int *);

/*De acordo com a situação escolhe uma decisão para ser tomada*/
void analizasituacaoaliens (t_jogo *, t_coord *, t_lista *);

/*Verifica se a necessida de remover bomba da lista*/
int vrfcrmbombaslista (t_jogo *);




