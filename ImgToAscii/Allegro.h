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

const char lightLevel[32][2];
const char reverseLightLevel[32][2];

typedef struct mouseInteract {
	bool pressed;
	int x, y;
}mouseInteract;

ALLEGRO_BITMAP* allBuffer;
ALLEGRO_DISPLAY* allDisplay;
ALLEGRO_TIMER* allTimer;
ALLEGRO_EVENT_QUEUE* allQueue;
ALLEGRO_EVENT allEvent;
ALLEGRO_TIMER* allTimer;
ALLEGRO_FONT* font;
ALLEGRO_FONT* bigfont;
mouseInteract mouse;

void InitTest(bool testRes, char* name);
void InitAllegroVars();
void extractAscii(unsigned char* image, int width, int height);
void EventHandler(bool* reDraw, unsigned char* image, int width, int height);