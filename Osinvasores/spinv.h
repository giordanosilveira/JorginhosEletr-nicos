/*player*/
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

/*Sprit explosão alien*/
#define EXPLOSAOA1 "\\\\  //"
#define EXPLOSAOA2 "-|10|-"
#define EXPLOSAOA3 "//  \\\\"

/*sprit explosão geral*/
#define EXPLOSAOG1 "\\ /"
#define EXPLOSAOG2 "-o-"
#define EXPLOSAOG3 "/ \\"

/*Tudo o que tem haver com a barreira*/
#define ALTURABARREIRA 3
#define LARGURABARREIRA 8

/*Tudo o que tem haver com o player*/
#define TAMPLAYER 7
#define ALTURAPLAYER 2

/*Tudo que tem haver com os aliens*/
#define SPRITSALIEN 18				/*Número de sprits por alien*/
#define QNTET 55
#define QNTDALIENTIROS 5
#define ESPACOCALIEN 2
#define ESPACOLALIEN 3
#define LINHASDALIENS 5
#define COLUNASDALIENS 11
#define TAMALIEN 6
#define VIVO 1
#define MORRENDO 0

/*Tamanho mínimo da tela*/
#define MINLINHAS 38
#define MINCOLUNAS 100

/*Tudo que tem haver com os tiros*/
#define QNTDTIROS 5 /*Quantidade de tiros por vez na tela*/
#define NPEGOU 0
#define PEGOU 1

/*Tudo o que tem haver com a dinamica do jogo*/
#define PERIODODOJOGO 40000
#define RESETACONTADOR 39999

struct t_coord {
	int x,y;
};
typedef struct t_coord t_coord;

struct t_alien {
	int status;
	t_coord pos;
	struct t_alien *prox;
	struct t_alien *prev;
};
typedef struct t_alien t_alien;

struct t_listAliens {
	t_alien *ini;
	t_alien *fim;
	int tam;
};
typedef struct t_listAliens t_listAliens;

/*esta struct serviva para eu fazer o controle da impressão dos aliens*/
struct t_controle {
	int *vetor;
	int tam;
};
typedef struct t_controle t_controle;

struct t_barreira {

	int status;
	t_coord chave;
	struct t_barreira *prox;
	struct t_barreira *prev;
};
typedef struct t_barreira t_barreira;

struct t_listaBarreira {
	t_barreira *ini;
	t_barreira *fim;
	int tam;
};
typedef struct t_listaBarreira t_listaBarreira;

struct t_tiro {
	int status;
	t_coord chave;
	struct t_tiro *prox;
	struct t_tiro *prev; /*linha/coluna*/
};
typedef struct t_tiro t_tiro;

struct t_listaTiros {
	t_tiro *ini;
	t_tiro *fim;
	t_tiro *atual;
	int tam;
};
typedef struct t_listaTiros t_listaTiros;


/*verifica se você ganhou*/
int ganhou (t_listAliens *);

/*cria uma lista vazia de aliens*/
void initaliens (t_listAliens *);

/*cria uma lista de tiros*/
void initiros (t_listaTiros *);

/*controla a inicialização da barreira*/
void inicializa_barreira (t_listaBarreira *, int, int);

/*cria uma lista de peças de barreira*/
void initbarreira (t_listaBarreira *);

/*insere o alien no final da lista*/
void insalienslista (t_listAliens *, int, int);

/*insere o tiro no final da lista*/
void instiroslista (t_listaTiros *,int , int);

/*insere a peça de barreira no final da lista*/
void inspecabarlista (t_listaBarreira *, int, int, int, int, int );

/*inicializa os sprites dos corpos dos aliens*/
void initspritsaliens (char **);

/*inicializa o sprite do player*/
void initspritplayer (char **);

/*inicializa os aliezinhos na lista*/
void inicializa_aliens (t_listAliens *);

void prntalienmorrendo (t_listAliens*, int*, int*);

/*print os aliens na posição atual*/
void prntaliens (t_listAliens *,char **,int *, int*, int*);

/*printa o player na posição atual*/
void prntplayer (char **, int *, int *);

/*printa a barreira na posicao certa*/
void prntbarreiras (t_listaBarreira *barreira);

/*Inicializa os vetores de controle*/
void inicializa_controle (t_controle *, t_controle *);

/*Vai administrar tudo o que tem haver com a impressão dos aliens*/
void admimpressao (t_listAliens *, char ** , int *, int *, int *, int *, t_controle *, t_controle *, int, int );

/*printa o tiro na tela*/
void  prntiro (t_listaTiros *);

/**/
t_coord srchalien (int, t_listAliens *, int, int);

/**/
void analizasituacao (int, t_coord *, t_listAliens *, t_listaBarreira *, char **, int *, int *, int *, int *);

/*remove o tiro certo da lista*/
void srchandrmtirolista (t_listaTiros *);

/*Printa as bombas dos alien*/
void prntiroaliens (t_listaTiros *); 
/*void srchanddstryalien ();*/
void attbarreira (t_listaBarreira *);

/*detecta se o tiro pegou em algo ou chegou no final da tela*/
int detecta_tiro (t_coord *, int *, t_listAliens *,t_listaBarreira *, int, int);
/*int detecta_tirosA ();*/
/*void analizasituacaoALIENS ();*/
