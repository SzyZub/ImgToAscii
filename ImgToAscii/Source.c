#include <stdlib.h>
#include <stdbool.h>
#include "Allegro.h"
#include "JpegHandler.h"

void DrawImage(unsigned char* image, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        al_draw_text(font, al_map_rgb(image[i], image[i + 1], image[i + 2]), (i % width) * 6, (int)(i / height * 6), 0, "T");
    }
}

void Draw(bool* reDraw, unsigned char* image, int width, int height) {
    al_set_target_bitmap(allBuffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    DrawImage(image, width, height);
    al_set_target_backbuffer(allDisplay);
    al_draw_scaled_bitmap(allBuffer, 0, 0, DISP_W, DISP_H, 0, 0, DISP_W, DISP_H, 0);
    al_flip_display();
    *reDraw = false;
}

int main() {
    InitAllegroVars();
    int width, height, channels;
    unsigned char* image_data = load_jpeg_file(&width, &height, &channels);
    image_data = resize_image(image_data, &width, &height, &channels);
    printf("%d %d", width, height);
    bool reDraw = true;
    while (true) {
        EventHandler(&reDraw);
        if (reDraw && al_is_event_queue_empty(allQueue)) {
            Draw(&reDraw, image_data, width, height);
        }
    }
}