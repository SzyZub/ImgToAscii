#pragma once
#include <stdio.h>
#include <jpeglib.h>
#define DISP_W 1200
#define DISP_H 900

unsigned char* load_jpeg_file(int* width, int *height, int* channels);
unsigned char* resize_image(unsigned char* input, int original_width, int original_height, int channels);