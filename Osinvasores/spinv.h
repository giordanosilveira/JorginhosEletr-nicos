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

/*Tamanho mínimo da tela*/
#define MINLINHAS 38
#define MINCOLUNAS 100

/*inicializa os sprites dos corpos dos aliens*/
void initspritsaliens (char **corposaliens);

/*inicializa os aliezinhos na lista*/
void inicializa_aliens (t_listALiens *l);

/*print os aliens na posição atual*/
void prntaliens ();

/*Vai administrar tudo o que tem haver com a impressão dos aliens*/
void admimpressao ();

