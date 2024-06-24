#include <stdlib.h>
#include <stdbool.h>
#include "Allegro.h"
#include "JpegHandler.h"

const char lightLevel[32][2] = { "`", ".", ",", ":", ";", "!", ">", "<", "~", "+", "_", "-", "?", "]", "[", "}", "{", "1", "r", "x", "X", "Y", "U", "O", "Z", "M", "W", "&", "8", "%", "B", "@" };
const char reverseLightLevel[32][2] = { "@", "B", "%", "8", "&", "W", "M", "Z", "O", "U", "Y", "X", "x", "r", "1", "{", "}", "[", "]", "?", "-", "_", "+", "~", "<", ">", "!", ";", ":", ",", ".", "`" };

void DrawImage(unsigned char* image, int width, int height) {
    for (int i = 0; i < width*height; i++) {
        unsigned char r = image[3 * i]; 
        unsigned char g = image[3 * i + 1];
        unsigned char b = image[3 * i + 2];
        int bright = ((int) (0.299 * r + 0.587 * g + 0.114 * b))/8;
        al_draw_text(font, al_map_rgb(255, 255, 255), (i % width) * FONTSIZE, (int)(i / width * FONTSIZE), 0, lightLevel[bright]);
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
    bool reDraw = true;
    while (true) {
        EventHandler(&reDraw);
        if (reDraw && al_is_event_queue_empty(allQueue)) {
            Draw(&reDraw, image_data, width, height);
            free(image_data);
        }
    }
}