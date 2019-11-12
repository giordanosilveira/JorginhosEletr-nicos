/*player*/
#define PLAYER11 " / \\ "
#define PLAYER12 "/MMMMM\\"

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

/*Tudo o que tem haver com o player*/
#define TAMPLAYER 7
#define ALTURAPLAYER 2

/*Tudo que tem haver com os aliens*/
#define SPRITSALIEN 18			/*Número de sprits por alien*/
#define QNTET 55
#define ESPACOCALIEN 2
#define ESPACOLALIEN 3
#define LINHASDALIENS 5
#define COLUNASDALIENS 11
#define TAMALIEN 6
#define VIVO 1
#define MORTO -1
#define MORRENDO 0

/*Tamanho mínimo da tela*/
#define MINLINHAS 38
#define MINCOLUNAS 100

#define QNTDTIROS 5 /*Quantidade de tiros por vez na tela*/
#define DELAY 100000

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
};
typedef struct t_listAliens t_listAliens;

/*esta struct serviva para eu fazer o controle da impressão dos aliens*/
struct t_controle {
	int *vetor;
	int tam;
};
typedef struct t_controle t_controle;

struct t_tiro {
	t_coord chave;
	t_tiro *prox;
	t_tiro *prev; /*linha/coluna*/
};
typedef t_tiro t_tiro;

struct t_listaTiro {
	t_tiro *ini;
	t_tiro *fim;
	t_tiro *atual;
	int tam;
};
typedef t_listaTiro t_listaTiro;


/*cria uma lista vazia de aliens*/
void initaliens (t_listAliens *);

/*cria uma lista de alien*/
void initiros (t_listaTiro *);

/*insere o alien no final da lista*/
void insalienslista (t_listAliens *, int, int);

/*insere o tiro no final da lista*/
void instiroslista (t_listaTiro *,int , int);

/*inicializa os sprites dos corpos dos aliens*/
void initspritsaliens (char **);

/*inicializa o sprite do player*/
void initspritplayer (char **);

/*inicializa os aliezinhos na lista*/
void inicializa_aliens (t_listAliens *);

/*print os aliens na posição atual*/
void prntaliens (t_listAliens *,char **,int *, int*, int*);

/*printa o player na posição atual*/
void prntplayer (char **, int *, int *);

/*Inicializa os vetores de controle*/
void inicializa_controle (t_controle *, t_controle *);

/*Vai administrar tudo o que tem haver com a impressão dos aliens*/
void admimpressao (t_listAliens *, char ** , int *, int *, int *, int *, t_controle *, t_controle *, int, int );

/*printa o tiro na tela*/
void  prntiro (char ,t_listaTiro *);
