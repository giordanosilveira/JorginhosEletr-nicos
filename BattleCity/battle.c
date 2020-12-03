
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_.h>
//#include <allegro5/allegro_.h>
//#include <allegro5/allegro_.h>
#include <stdio.h>

#define FPS 60.0
#define ESQUERDA -1
#define DIREITA 1
#define SOBE 2
#define DESCE 0
#define ATIRANDO 1
#define MENU 0
#define JOGANDO 1
#define PERDEU 2
#define GANHOU 3
#define FIMDEJOGO 4
#define W_BUFFER 480
#define H_BUFFER 360
#define ESCALA 30
#define DISP_SCALE 2
#define WDISPLAY 960
#define HDISPLAY 720
#define S_BLOCO 34
#define H_TIRO 8
#define W_TIRO 20
#define H_TANKES 24
#define W_TANKES 24

typedef struct {
    int pos_x, pos_y;
    int w_sprite, h_sprite;
    int vida;
    int atirando;
}t_sprite;
typedef struct {
    int linha, coluna;
    int **matriz;
}t_mapa;


ALLEGRO_TIMER *timer;
ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *fila_eventos;
ALLEGRO_FONT *fonte;
ALLEGRO_BITMAP *blocos;
ALLEGRO_BITMAP *tiros[2];
ALLEGRO_BITMAP *player;
ALLEGRO_BITMAP *inimigo;
ALLEGRO_BITMAP *buffer;

int estado_jogo;
int escala;
bool desenha;

t_mapa mapa;

//inicializa as estruturas do jogo
void inicializar ();

//Destroi as estruturas usadas
void destroy ();

//Inicializando as estruturas do mapa
void initmapa(const char *);

//Estado em que o jogandor está jogando
void jogando ();

//Desenha num buffer bitmap antes de desenha na tela (facilita conversão)
void disp_pre_draw ();

int main () {

    inicializar ();

    while (estado_jogo != FIMDEJOGO) {

        if (estado_jogo == JOGANDO) {
            jogando ();
        }
    }

    destroy ();
    return 0;
}
void destroy () {
    
    if (display)
        al_destroy_display (display);

    if (timer)
        al_destroy_timer (timer);

    if (fila_eventos)
        al_destroy_event_queue (fila_eventos);

    if (blocos)
        al_destroy_bitmap (blocos);

    if (tiros[0])
        al_destroy_bitmap (tiros[0]);
    
    if (tiros[1])
        al_destroy_bitmap (tiros[1]);

    if (fonte)
        al_destroy_font (fonte);

    if (player)
        al_destroy_bitmap (player);
    
    if (inimigo)
        al_destroy_bitmap (inimigo);

    if (buffer)
        al_destroy_bitmap (buffer);

}

void disp_pre_draw () {
    al_set_target_bitmap (buffer);
}

void disp_post_draw () {

    al_set_target_backbuffer(display);
    al_draw_scaled_bitmap (buffer, 0, 0, W_BUFFER, H_BUFFER, 0, 0, WDISPLAY, HDISPLAY, 0);
    al_flip_display ();

}
void inicializar () {

    estado_jogo = JOGANDO;

    if (!al_init()) {
        printf ("Não foi possível abrir a bibioteca allegro\n");
        exit (1);
    }

    if (!al_init_image_addon()) {
        printf ("Image addon não foi inicializada\n");
        exit (1);
    }

    timer = al_create_timer (1.0/FPS);
    if (!timer) {
        printf ("Não foi possível criar um temporizador\n");
        destroy ();
        exit(1);
    }

    display = al_create_display (WDISPLAY,HDISPLAY);
    if (!display) {
        printf ("Não foi possível criar uma tela de jogo\n");
        destroy ();
        exit (1);
    }

    buffer = al_create_bitmap (W_BUFFER, H_BUFFER);
    if (!buffer) {
        printf ("Não foi possível criar um buffer para a imagem\n");
        destroy ();
        exit (1);
    }
    if (! al_install_keyboard()) {
        printf ("Não foi possível reconhecer o teclado\n");
        exit (1);
    }

    fila_eventos = al_create_event_queue();
    if (!fila_eventos) {
        printf ("Não foi possível criar uma fila de eventos\n");
        destroy ();
        exit (1);
    }

    blocos = al_load_bitmap ("resources/bloco.png");
    if (!blocos) {
        printf ("Não foi possível abrir a imagem bloco\n");
        destroy ();
        exit (1);
    }

    tiros[0] = al_load_bitmap ("resources/tiros.png");
    tiros[1] = al_load_bitmap ("resources/tiro2.png");
    if ((!tiros[0]) || (!tiros[1])) {
        printf ("Não foi possível abrir a imagem tiros\n");
        destroy ();
        exit (1);
    }

    player = al_load_bitmap ("resources/player2.png");
    if (!player) {
        printf ("Não foi possível abrir a imagem player\n");
        destroy ();
        exit (1);
    }

    inimigo = al_load_bitmap ("resources/inimigo1.png");
    if (!inimigo) {
        printf ("Não foi possível abrir a imagem inimigo.png");
        destroy ();
        exit (1);
    }

    al_init_font_addon ();
    if (! al_init_ttf_addon ()) {
        printf ("Falha ao inicializar add-on para fontes .ttf\n");
        exit(1);
    }

    fonte = al_load_font ("resources/Mariofonte.ttf", 16, 0);
    if (!fonte) {
        printf ("Não foi possível carregar a fonte\n");
        destroy ();
        exit (1);
    }

    al_register_event_source (fila_eventos, al_get_display_event_source(display));
    al_register_event_source (fila_eventos, al_get_keyboard_event_source());
    al_register_event_source (fila_eventos, al_get_timer_event_source(timer));

    al_start_timer (timer);

    initmapa ("mapa.dat");

    escala = H_BUFFER/mapa.linha;
    estado_jogo = JOGANDO;

}
void initmapa (const char *arquivo){

    FILE *arq;

    arq = fopen (arquivo, "r");
    if (!arq) {
        printf ("Não foi possível abrir o arquivo mapa\n");
        exit (1);
    }

    if (fscanf (arq, "%d %d", &mapa.linha, &mapa.coluna) != 2) {
        printf ("Não foi possível ler o tamanho do mapa\n");
        exit (1);
    }

    mapa.matriz = malloc(sizeof(int *)*mapa.linha);
    if (! mapa.matriz) {
        printf ("Não foi possível alocar espaço para a matriz\n");
        exit (0);
    }

    for (int i = 0; i < mapa.linha; i++) {
        mapa.matriz[i] = malloc (sizeof(int)*mapa.coluna);
        if (! mapa.matriz[i]) {
            printf ("Não foi possível alocar espaço para as colunas da matriz\n");
            exit (1);
        }
    }

    for (int i = 0; i < mapa.linha; i++) {
        for (int j = 0; j < mapa.coluna; j++) {
            if (! fscanf (arq, "%d", &mapa.matriz[i][j])) {
                printf ("Não foi possível carregar os itens da matriz\n");
                exit (1);
            }
        }
    }

}
void jogando () {

    ALLEGRO_EVENT evento;

    al_wait_for_event (fila_eventos, &evento);

    if (evento.type == ALLEGRO_EVENT_TIMER)
        desenha = true;

    else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        estado_jogo = FIMDEJOGO;
    }

    else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
        estado_jogo = FIMDEJOGO;
    }

    if (desenha && al_is_event_queue_empty (fila_eventos)) {

        disp_pre_draw ();
        al_clear_to_color (al_map_rgb(128,128,128));

        for (int i = 0; i < mapa.linha; i++){
            for (int j = 0; j < mapa.coluna; j++) {
                if (mapa.matriz[i][j] == 1)
                    al_draw_bitmap (blocos, ESCALA * j - 4, ESCALA * i - 4, 0);
                    //al_draw_scaled_bitmap (blocos, 0, 0, S_BLOCO, S_BLOCO, escala * j, escala * i, W_BUFFER/9, H_BUFFER/7, 0);
            }
        }
        al_draw_bitmap (player, 240, 240, 0);
        //al_draw_scaled_bitmap (player, 0, 0, );
        //al_draw_rotated_bitmap (player, 0, 0, 12 * escala, 9 * escala, 12, 0);
        disp_post_draw ();
        desenha = false;
    }
}  