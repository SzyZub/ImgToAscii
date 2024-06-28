#include <stdlib.h>
#include <stdbool.h>
#include "Allegro.h"
#include "JpegHandler.h"

bool darkmode = true;
bool color = true;
bool menu = true;
bool generated = false;

void DrawImage(unsigned char* image, int width, int height) {
        for (int i = 0; i < width * height; i++) {
            unsigned char r = image[3 * i];
            unsigned char g = image[3 * i + 1];
            unsigned char b = image[3 * i + 2];
            int bright = ((int)(0.299 * r + 0.587 * g + 0.114 * b)) / 8;
            if (!color) {
                if (darkmode) {
                    r = 245;
                    g = 245;
                    b = 245;
                }
                else {
                    r = 0;
                    g = 0;
                    b = 0;
                }
            }
            if (darkmode)
                al_draw_text(font, al_map_rgb(r, g, b), (i % width) * FONTSIZE, (int)(i / width * FONTSIZE), 0, lightLevel[bright]);
            else
                al_draw_text(font, al_map_rgb(r, g, b), (i % width) * FONTSIZE, (int)(i / width * FONTSIZE), 0, reverseLightLevel[bright]);
        }
        generated = true;
}

void DrawDrawing(bool* reDraw, unsigned char** image, int width, int height) {
    if (!generated) {
        al_set_target_bitmap(allBuffer);
        if (darkmode)
            al_clear_to_color(al_map_rgb(0, 0, 0));
        else
            al_clear_to_color(al_map_rgb(255, 255, 255));
        DrawImage(*image, width, height);
        al_draw_filled_rectangle(0, 900, 1200, 950, al_map_rgb(235, 235, 235));
        al_draw_text(bigfont, al_map_rgb(10, 10, 10), (0 + 1200) / 2, (900 + 950 - al_get_font_line_height(bigfont)) / 2, ALLEGRO_ALIGN_CENTRE, "Back to Menu");
        al_set_target_backbuffer(allDisplay);
        al_draw_scaled_bitmap(allBuffer, 0, 0, DISP_W, DISP_H, 0, 0, DISP_W, DISP_H, 0);
        al_flip_display();
        *reDraw = false;
    }
    if (mouse.pressed == true) {
        mouse.pressed = false;
        if (mouse.y > 900) {
            menu = true;
            generated = false;
        }
    }
}

void DrawRectangle(int x, int y, int x2, int y2, ALLEGRO_COLOR col, char label[10], bool light) {
    al_draw_filled_rectangle(x, y,x2, y2, col);
    if (light) {
        al_draw_rectangle(x, y, x2, y2, al_map_rgb(30, 200, 122), 5);
    }
    else {
        al_draw_rectangle(x, y, x2, y2, al_map_rgb(166, 30, 50), 5);
    }
    al_draw_text(bigfont, al_map_rgb(10, 10, 10), (x2 + x)/2, (y + y2 - al_get_font_line_height(bigfont)) / 2, ALLEGRO_ALIGN_CENTRE, label);
}

void DrawMenu(bool* reDraw) {
    al_set_target_bitmap(allBuffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    DrawRectangle(200, 100, 580, 300, al_map_rgb(235, 235, 235), "Dark", darkmode);
    DrawRectangle(620, 100, 1000, 300, al_map_rgb(235, 235, 235), "Light", !darkmode);
    DrawRectangle(200, 400, 580, 600, al_map_rgb(235, 235, 235), "Color", color);
    DrawRectangle(620, 400, 1000, 600, al_map_rgb(235, 235, 235), "No Color", !color);
    al_draw_filled_rectangle(380, 700, 820, 800, al_map_rgb(235, 235, 235));
    al_draw_text(bigfont, al_map_rgb(10, 10, 10), (380 + 820) / 2, (700 + 800 - al_get_font_line_height(bigfont)) / 2, ALLEGRO_ALIGN_CENTRE, "Show");
    al_set_target_backbuffer(allDisplay);
    al_draw_scaled_bitmap(allBuffer, 0, 0, DISP_W, DISP_H, 0, 0, DISP_W, DISP_H, 0);
    al_flip_display();
    *reDraw = false;
    if (mouse.pressed == true) {
        mouse.pressed = false;
        if (mouse.y > 100 && mouse.y < 300) {
            if (mouse.x > 200 && mouse.x < 580)
                darkmode = true;
            else if (mouse.x > 620 && mouse.x < 1000)
                darkmode = false;
        }
        else if (mouse.y > 400 && mouse.y < 600) {
            if (mouse.x > 200 && mouse.x < 580)
                color = true;
            else if (mouse.x > 620 && mouse.x < 1000)
                color = false;
        }
        else if (mouse.y > 700 && mouse.y < 800 && mouse.x > 380 && mouse.x < 820){
            menu = false;
        }
    }
}

int main() {
    InitAllegroVars();
    int width, height, channels;
    unsigned char* image_data = load_jpeg_file(&width, &height, &channels);
    image_data = resize_image(image_data, &width, &height, &channels);
    bool reDraw = true;
    mouse.pressed = false;
    while (true) {
        EventHandler(&reDraw, image_data, width, height);
        if (reDraw && al_is_event_queue_empty(allQueue)) {
            if (!menu) {
                DrawDrawing(&reDraw, &image_data, width, height);
            }
            else {
                DrawMenu(&reDraw);
            }
        }
    }
}