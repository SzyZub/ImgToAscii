#include "Allegro.h"


void InitTest(bool testRes, char* name)
{
    if (testRes) {
        return;
    }
    fprintf(stderr, "couldn't initialize %s\n", name);
    exit(-2);
}

void InitAllegroVars()
{
    InitTest(al_init(), "allegro");
    InitTest(al_init_font_addon(), "font addon");
    InitTest(al_init_ttf_addon(), "ttf");
    font = al_load_ttf_font("font.ttf", FONTSIZE, 0);
    InitTest(font, "font.ttf");
    allBuffer = al_create_bitmap(DISP_W, DISP_H);
    InitTest(allBuffer, "bitmap allBuffer");
    allDisplay = al_create_display(DISP_W, DISP_H);
    InitTest(allDisplay, "allDisplay");
    allTimer = al_create_timer(1.0 / FRAMERATE);
    InitTest(allTimer, "allTimer");
    allQueue = al_create_event_queue();
    InitTest(allQueue, "allQueue");
    al_register_event_source(allQueue, al_get_display_event_source(allDisplay));
    al_register_event_source(allQueue, al_get_timer_event_source(allTimer));
    al_start_timer(allTimer);
}
void EventHandler(bool* reDraw) {
    al_wait_for_event(allQueue, &allEvent);
    switch (allEvent.type) {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        exit(-1);
        break;
    }
}