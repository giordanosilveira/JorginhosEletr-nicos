/*
  Feito por Marcos Castiho para a disciplina CI1001 - Programacao I
  Em 18/10/2019.
  Define a estrutura de dados para o Tipo Abstrato de Dados Lista
  como sendo uma lista duplamente encadeada com sentinelas no inicio
  e no final. A cabeca da lista tem ponteiros para o inicio, fim e
  para um elemento qualquer da lista, alem do tamanho da lista.
  Contem os prototipos publicos das funcoes que manipulam o TAD.
*/


/*status alien*/
#define VIVO 1 
#define MORTO -1
#define MORRENDO 0

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

/*
  Cria uma lista vazia. Ela eh duplamente encadeada e tem sentinelas no
  inicio e no final. Tambem tem um apontador para um elemento qualquer.
*/
int inicializa_lista(t_listAliens *l);


/*
  Remove todos os elementos da lista e faz com que ela aponte para NULL.
void destroi_lista(t_listAliens *l);

*/

/*
  Insere o elemento item no final da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
int insere_fim_lista(int item, t_listAliens *l);
