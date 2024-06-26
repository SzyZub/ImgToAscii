#pragma once
#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>
#include <stdlib.h>

#define MAXWIDTH 120
#define MAXHEIGHT 90

unsigned char* load_jpeg_file(int* width, int *height, int* channels);
unsigned char* resize_image(unsigned char* input, int *original_width, int *original_height, int *channels);