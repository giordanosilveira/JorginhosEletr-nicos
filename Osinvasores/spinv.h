/*Alien 1*/
#define ALIEN11 "/T-T\\"
#define ALIEN12 "()-()"
#define ALIEN13 "|W-W|"
#define ALIEN112 "/*-*\\"
#define ALIEN122 "/(|)\\"
#define ALIEN132 "|W-W|"

/*Alien 2*/
#define ALIEN21 "(º-º)"
#define ALIEN22 "}MOM{"
#define ALIEN23 "().()"
#define ALIEN212 "(¬.¬)"
#define ALIEN222 "{MAM}"
#define ALIEN232 "()_()"

/*Alien 3*/
#define ALIEN31 "(O.O)"
#define ALIEN32 "|/*\\|"
#define ALIEN33 ")WTW("
#define ALIEN312 "(O.O)"
#define ALIEN322 "/|*|\\"
#define ALIEN332 "(WTW)"

#define QNTCORPOS 18 /*quantidades de corpos*/

#define TAMET 6 /*tamanho do et*/
struct t_alien {

	int status;
	int versao;
	int pslinha; /*guarda a posição da linha*/
	int pscoluna; /*guarda a posição da coluna*/
	struct t_alien *prox;
	struct t_alien *prev;
};
typedef struct t_alien t_alien;
