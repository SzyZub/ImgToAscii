#include "Allegro.h"

const char lightLevel[32][2] = { "`", ".", ",", ":", ";", "!", ">", "<", "~", "+", "_", "-", "?", "]", "[", "}", "{", "1", "r", "x", "X", "Y", "U", "O", "Z", "M", "W", "&", "8", "%", "B", "@" };
const char reverseLightLevel[32][2] = { "@", "B", "%", "8", "&", "W", "M", "Z", "O", "U", "Y", "X", "x", "r", "1", "{", "}", "[", "]", "?", "-", "_", "+", "~", "<", ">", "!", ";", ":", ",", ".", "`" };

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
    InitTest(al_init_primitives_addon(), "primitives");
    font = al_load_ttf_font("font.ttf", FONTSIZE, 0);
    InitTest(font, "font.ttf");
    bigfont = al_load_ttf_font("font.ttf", FONTSIZE*3, 0);
    InitTest(bigfont, "font.ttf");
    allBuffer = al_create_bitmap(DISP_W, DISP_H);
    InitTest(allBuffer, "bitmap allBuffer");
    allDisplay = al_create_display(DISP_W, DISP_H);
    InitTest(allDisplay, "allDisplay");
    allTimer = al_create_timer(1.0 / FRAMERATE);
    InitTest(allTimer, "allTimer");
    allQueue = al_create_event_queue();
    InitTest(allQueue, "allQueue");
    InitTest(al_install_mouse(), "mouse");
    al_register_event_source(allQueue, al_get_mouse_event_source());
    al_register_event_source(allQueue, al_get_display_event_source(allDisplay));
    al_register_event_source(allQueue, al_get_timer_event_source(allTimer));
    al_start_timer(allTimer);
}

void extractAscii(unsigned char* image, int width, int height) {
    FILE* infile = fopen("ImageFolder/ascii.txt", "w");
    for (int i = 0; i < width * height; i++) {
        unsigned char r = image[3 * i];
        unsigned char g = image[3 * i + 1];
        unsigned char b = image[3 * i + 2];
        int bright = ((int)(0.299 * r + 0.587 * g + 0.114 * b)) / 8;
        if (i % width == 0 && i != 0) {
            fprintf(infile, "\n");
        }
        fprintf(infile, "%c%c", reverseLightLevel[bright][0], reverseLightLevel[bright][0]);

    }
    fclose(infile);
}

void EventHandler(bool* reDraw, unsigned char* image, int width, int height) {
    al_wait_for_event(allQueue, &allEvent);
    switch (allEvent.type) {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        extractAscii(image, width, height);
        exit(-1);
        break;
    case ALLEGRO_EVENT_TIMER:
        *reDraw = true;
        break;
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        if (allEvent.mouse.button == 1) {
            mouse.x = allEvent.mouse.x;
            mouse.y = allEvent.mouse.y;
            mouse.pressed = true;
        }
    break;
    }
}