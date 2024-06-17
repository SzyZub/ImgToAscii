#include <stdlib.h>
#include <stdbool.h>
#include "Allegro.h"
#include "JpegHandler.h"

void DrawImage(unsigned char* image) {
    for (int i = 0; i < DISP_W; i++) {
        for (int j = 0; j < DISP_H; j++) {

        }
    }
}

void Draw(bool* reDraw, unsigned char* image) {
    al_set_target_bitmap(allBuffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    DrawImage(image);
    al_set_target_backbuffer(allDisplay);
    al_draw_scaled_bitmap(allBuffer, 0, 0, DISP_W, DISP_H, 0, 0, DISP_W, DISP_H, 0);
    al_flip_display();
    reDraw = false;
}

int main() {
    bool reDraw = false;
    InitAllegroVars();
    int width, height, channels;
    unsigned char* image_data = load_jpeg_file(&width, &height, &channels);
    while (true) {
        EventHandler(&reDraw);
        if (reDraw && al_is_event_queue_empty(allQueue)) {
            Draw(&reDraw, image_data);
        }
    }
}