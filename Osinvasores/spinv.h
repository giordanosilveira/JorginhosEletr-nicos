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

/*Tudo o que tem haver com a barreira*/
#define ALTURABARREIRA 3
#define LARGURABARREIRA 8

/*Tudo o que tem haver com o player*/
#define TAMPLAYER 7
#define ALTURAPLAYER 2

/*Tudo que tem haver com os aliens*/
#define SPRITSALIEN 18		/*Número de sprits por alien*/
#define QNTET 55
#define QNTDALIENTIROS 6
#define ESPACOCALIEN 2
#define ESPACOLALIEN 3
#define LINHASDALIENS 5
#define COLUNASDALIENS 11
#define TAMALIEN 6
#define VIVO 1
#define MORRENDO 0

/*Tudo o que tem haver com a nave mae*/
#define ALTURANAVEMAE 3
#define LARGURANAVEMAE 3

/*Tamanho mínimo da tela*/
#define MINLINHAS 40
#define MINCOLUNAS 120

/*Tudo que tem haver com os tiros*/
#define QNTDTIROS 4 /*Quantidade de tiros por vez na tela*/
#define NPEGOU 0
#define PEGOU 1

/*Tudo o que tem haver com a dinamica do jogo*/
#define PERIODODOJOGO 40000
#define RESETACONTADOR 39999

struct t_coord {
	int x,y;
};
typedef struct t_coord t_coord;

struct t_navemae {
	t_coord coord;
	int status;
};
typedef struct t_navemae t_navemae;

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
	t_coord vetor[11];
	int fim;
	int ini;
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

/*verifica se o jogador perdeu*/
int perdeu (int );

/*verifica se você ganhou*/
int ganhou (t_listAliens *);

/*cria uma lista vazia de aliens*/
void initaliens (t_listAliens *);

/*cria a struct que vai me ajudar no controle de impressão dos alien*/
void initcontrole (t_controle *, int, int);

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

/*retorna as coordenadas certas do alien que atirou */
t_coord srchalien (int, t_listAliens *, int, int);

/*De acordo com a situação analiza a decisão a ser tomada*/
void analizasituacao (int, t_coord *,t_coord *, t_listAliens *, t_listaBarreira *, t_listaTiros *,t_navemae , char **, char **, int *, int *, int *, int *, int *);

/*remove o tiro certo da lista*/
void srchandrmtirolista (t_listaTiros *);

/*Printa as bombas dos alien*/
void prntiroaliens (t_listaTiros *);

/*Pesquisa qual alien esta morrendo e mata ele*/
void srchanddstryalien (t_listAliens *, t_coord *);

void attbarreira (t_listaBarreira *);

/*detecta se o tiro pegou em algo ou chegou no final da tela*/
int detecta_tiro (t_coord *, int *, t_listAliens *,t_listaBarreira *,t_listaTiros *,t_navemae *, int, int);

/*verifica se a bomba do alien pegou em algo*/
int detecta_bomba (t_coord *, int *, t_listaBarreira *, int , int, int);

/*De acordo com a situação analiza a decisao a ser tomada (ALIENS)*/
void analizasituacaoALIENS (int, t_coord *, t_listaBarreira *, int *, int *);

/*printa player morrendo*/
void prntplayermorto (int, int);

/*printa a colisao do tiro*/
void prntclstiro (t_coord *);

/*Inicializa o sprit da nave mae*/
void initspritnavemae (char **);

/*Printa a nave mae*/
void prntnavemae (char **, t_navemae);

/*verifica os extremos dos aliens*/
void vrfcextraliens (t_coord, t_controle *);
