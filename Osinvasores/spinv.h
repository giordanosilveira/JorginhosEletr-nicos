
/*Sprits Alien 1*/
#define ALIEN11 "/T-T\\"
#define ALIEN12 "()-()"
#define ALIEN13 "|W-W|"
#define ALIEN112 "/*-*\\"
#define ALIEN122 "/(|)\\"
#define ALIEN132 "|W-W|"

/*Sprits Alien 2*/
#define ALIEN21 "(º-º)"
#define ALIEN22 "}MOM{"
#define ALIEN23 "().()"
#define ALIEN212 "(¬.¬)"
#define ALIEN222 "{MAM}"
#define ALIEN232 "()_()"

/*Sprits Alien 3*/
#define ALIEN31 "(O.O)"
#define ALIEN32 "|/*\\|"
#define ALIEN33 ")WTW("
#define ALIEN312 "(O.O)"
#define ALIEN322 "/|*|\\"
#define ALIEN332 "(WTW)"

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

#define DELAY 105000

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

/*cria uma lista vazia de aliens*/
void initaliens (t_listAliens *);

/*insere o alien no final da lista*/
void insalienslista (t_listAliens *, int, int);

/*inicializa os sprites dos corpos dos aliens*/
/*void initspritsaliens (char **);*/

/*inicializa os aliezinhos na lista*/
void inicializa_aliens (t_listAliens *);

/*print os aliens na posição atual*/
void prntaliens (t_listAliens *,char **,int *, int*, int*);

/*Vai administrar tudo o que tem haver com a impressão dos aliens*/
void admimpressao ();

