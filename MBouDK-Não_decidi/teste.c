#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include <stdio.h>

#define FPS 60.0
#define LARGURATELA 600
#define ALTURATELA 800
#define MENU 1
#define PREJOGO 2
#define JOGANDO 3
#define PAUSA 4
#define GAMEOVER 5
#define GANHOU 6
#define PERDEU 7
#define FIMDEPARTIDA 8

ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* fila_eventos;
ALLEGRO_DISPLAY* display;
ALLEGRO_FONT* fonte;
ALLEGRO_EVENT evento;
ALLEGRO_BITMAP * titulo;
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

        /*else if (estado_jogo == PREJOGO) {
            prejogo();
        }
        else if (estado_jogo == JOGANDO) {
            jogando ();
        }
        else if (estado_jogo == FIMDEPARTIDA) {
            fimDePartida ();
        }*/

        /*

        if (evento.type == ALLEGRO_EVENT_TIMER)
            redraw = true;

        else if ((evento.type == ALLEGRO_EVENT_KEY_DOWN) || (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;

        if (redraw && al_is_event_queue_empty(fila_eventos)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(fonte, al_map_rgb(255, 0, 255), 0, 0, 0, "Hello world!");
            al_flip_display ();

            redraw = false;
        }
    }*/
    
    }

    al_destroy_font (fonte);
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

    fonte = al_create_builtin_font ();
    
    al_register_event_source (fila_eventos, al_get_keyboard_event_source());
    al_register_event_source (fila_eventos, al_get_display_event_source(display));
    al_register_event_source (fila_eventos, al_get_timer_event_source(timer));

    al_start_timer (timer);

    estado_jogo = MENU;
}

void menu () {

    al_wait_for_event (fila_eventos, &evento);

    if (evento.type == ALLEGRO_EVENT_TIMER)
        redraw = true;

    else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        estado_jogo == GAMEOVER;
    }

    /*else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            estado_jogo == GAMEOVER;
        else if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
            estado_jogo == GAMEOVER;
    }*/

    if (redraw && al_is_event_queue_empty(fila_eventos)) {
        al_clear_to_color (al_map_rgb(65, 105, 255));
        al_draw_text (fonte, al_map_rgb(0, 0, 0), LARGURATELA/2, 400, 0, "APERTE ENTER PARA JOGAR");
        al_draw_text (fonte, al_map_rgb(0, 0 ,0), LARGURATELA/2, 400 + 20, 0, "APERTE ESC PARA SAIR");
        al_draw_bitmap (titulo, LARGURATELA/2, ALTURATELA - 600, 0);
        al_flip_display ();
    } 

}