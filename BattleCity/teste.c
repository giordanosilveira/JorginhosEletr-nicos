#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>

#define FPS 60.0
#define ALTURATELA 800
#define LARGURATELA 600
#define MENU 1
#define PREJOGO 2
#define JOGANDO 3
#define PAUSA 4
#define GAMEOVER 5
#define GANHOU 6
#define PERDEU 7
#define FIMDEPARTIDA 8
#define VELOCIDADE 5

typedef struct 
{
    int pos_x, pos_y;
    int largura_sprite, altura_sprite;
    int caindo;
    int colunas_sprites, linhas_sprites;
} sprites;

typedef struct 
{
    ALLEGRO_FONT* fonte_grande;
    ALLEGRO_FONT* fonte_pequena;
    ALLEGRO_FONT* fonte_pontuacao;
}t_fonte;



ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* fila_eventos;
ALLEGRO_DISPLAY* display;
ALLEGRO_BITMAP * titulo;
ALLEGRO_BITMAP* solo;
ALLEGRO_BITMAP* montanha;

t_fonte fonte;
sprites s_titulo;
sprites s_solo;
sprites s_montanha;

int estado_jogo;
bool redraw = true;

//Inicializa as estruturas, as funçoẽs, enfim tudo o que tem haver com o programa
void inicializar (void);

//Mostra o menu
void menu (void);


int main () {

    inicializar ();

    while (estado_jogo != GAMEOVER) {

        if (estado_jogo == MENU) {
            menu ();
        }
    
    }

    al_destroy_font (fonte.fonte_grande);
    al_destroy_font (fonte.fonte_pequena);
    al_destroy_font (fonte.fonte_pontuacao);
    al_destroy_display (display);
    al_destroy_timer (timer);
    al_destroy_event_queue (fila_eventos);
    return 0;
}

void inicializar () {

    if (! al_init()) {
        printf ("Não foi possível abrir a bibioteca allegro\n");
        exit (1);
    }

    if (! al_init_image_addon ()) {
        printf ("Não será possível adicionar imagens\n");
        exit (1);
    }

    timer = al_create_timer (1.0/FPS);
    if (!timer) {
        printf ("Não foi possível criar um temporizador");
        exit (1);
    }

    display = al_create_display (ALTURATELA, LARGURATELA);
    if (! display){
        printf ("Não foi possível criar o display\n");
        exit (1);
    }

    if (! al_install_keyboard()){
        printf ("Não foi possível reconhecer o teclado\n");
        exit (1);
    }

    fila_eventos = al_create_event_queue ();
    if (! fila_eventos) {
        printf ("Não foi possível criar uma fila de eventos\n");
        exit (1);
    }

    titulo = al_load_bitmap ("resources/Título.png");
    if (!titulo) {
        printf ("Não foi possível abrir a imagem titulo\n");
        al_destroy_timer (timer);
        al_destroy_display (display);
        al_destroy_event_queue (fila_eventos);
        exit (1);
    }
    s_titulo.largura_sprite = al_get_bitmap_width (titulo);
    s_titulo.altura_sprite = al_get_bitmap_height (titulo);

    solo = al_load_bitmap ("resources/Chaotitulo.png");
    if (!solo) {
        printf ("Não foi possível abrir a imagem solo\n");
        al_destroy_timer (timer);
        al_destroy_display (display);
        al_destroy_event_queue (fila_eventos);
        exit (1);
    }
    s_solo.largura_sprite = al_get_bitmap_width (solo);
    s_solo.altura_sprite = al_get_bitmap_height (solo);

    montanha = al_load_bitmap ("resources/mariomontanha.png");
    if (!montanha) {
        printf ("Não foi possível abrir a imagem solo\n");
        al_destroy_timer (timer);
        al_destroy_display (display);
        al_destroy_event_queue (fila_eventos);
        exit (1);
    }
    s_montanha.largura_sprite = al_get_bitmap_width (montanha);
    s_montanha.altura_sprite = al_get_bitmap_height (montanha);

    al_init_font_addon ();
    if (! al_init_ttf_addon ()){
        printf ("Falha ao inicializar add-on para fontes .ttf");
        exit (1);
    }
    fonte.fonte_grande = al_load_font ("resources/Mariofonte.ttf", 16, 0);
    fonte.fonte_pequena = al_load_font ("resources/Mariofonte.ttf", 10, 0);
    fonte.fonte_pontuacao = al_load_font ("resources/Mariofonte.ttf", 40, 0);
    if (!fonte.fonte_grande || !fonte.fonte_pequena || !fonte.fonte_pontuacao){
        printf ("Não foi possível carregar as fontes\n");
        exit (1);
    }

    al_register_event_source (fila_eventos, al_get_display_event_source(display));
    al_register_event_source (fila_eventos, al_get_keyboard_event_source());
    al_register_event_source (fila_eventos, al_get_timer_event_source(timer));

    al_start_timer (timer);

    estado_jogo = MENU;
}

void menu () {

    ALLEGRO_EVENT evento;
    
    al_wait_for_event (fila_eventos, &evento);

    if (evento.type == ALLEGRO_EVENT_TIMER)
        redraw = true;

    else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        estado_jogo = GAMEOVER;
    }

    else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            estado_jogo = GAMEOVER;
        else if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
            estado_jogo = GAMEOVER;
    }

    if (redraw && al_is_event_queue_empty(fila_eventos)) {
        al_clear_to_color (al_map_rgb(65, 105, 255));
        al_draw_scaled_bitmap (montanha, 0,0, s_montanha.largura_sprite, s_montanha.altura_sprite, 0, 325, s_montanha.largura_sprite + 300, s_montanha.altura_sprite + 150, 0);
        al_draw_text (fonte.fonte_grande, al_map_rgb(255, 255, 255), LARGURATELA/2 - 90, 330, 0, "APERTE ENTER PARA JOGAR");
        al_draw_text (fonte.fonte_grande, al_map_rgb(255, 255 ,255), LARGURATELA/2 - 90, 330 + 60, 0, "APERTE ESC PARA SAIR");
        al_draw_scaled_bitmap (titulo, 0, 0, s_titulo.largura_sprite, s_titulo.altura_sprite, LARGURATELA/2 - 300/2, 100, s_titulo.largura_sprite + 300, s_titulo.altura_sprite + 100, 0);
        al_draw_scaled_bitmap (solo,0,0, s_solo.largura_sprite, s_solo.altura_sprite, 0, 516, s_solo.largura_sprite + 600, s_solo.altura_sprite + 60, 0);
 //     al_draw_bitmap (titulo, LARGURATELA/2, ALTURATELA - 600, 0);
        redraw = false;

        al_flip_display ();
    } 

}