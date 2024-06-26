#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#define DISP_W 1200
#define DISP_H 950
#define FRAMERATE 10
#define FONTSIZE 10


ALLEGRO_BITMAP* allBuffer;
ALLEGRO_DISPLAY* allDisplay;
ALLEGRO_TIMER* allTimer;
ALLEGRO_EVENT_QUEUE* allQueue;
ALLEGRO_EVENT allEvent;
ALLEGRO_TIMER* allTimer;
ALLEGRO_FONT* font;
ALLEGRO_FONT* bigfont;

void InitTest(bool testRes, char* name);
void InitAllegroVars();
void EventHandler(bool* reDraw);