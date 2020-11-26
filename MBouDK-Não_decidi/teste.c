#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>

#define FPS 60.0

ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* fila_eventos;
ALLEGRO_DISPLAY* display;
ALLEGRO_FONT* fonte;
ALLEGRO_EVENT evento;

int main () {

    al_init();
    al_install_keyboard();

    timer = al_create_timer (1.0/FPS);
    fila_eventos = al_create_event_queue ();
    display = al_create_display (640, 400);
    fonte = al_create_builtin_font ();

    al_register_event_source (fila_eventos, al_get_keyboard_event_source());
    al_register_event_source (fila_eventos, al_get_display_event_source(display));
    al_register_event_source (fila_eventos, al_get_timer_event_source(timer));

    bool redraw = true;

    al_start_timer (timer);

    while (1) {
        al_wait_for_event (fila_eventos, &evento);

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
    }
    
    al_destroy_font (fonte);
    al_destroy_display (display);
    al_destroy_timer (timer);
    al_destroy_event_queue (fila_eventos);

    return 0;
}