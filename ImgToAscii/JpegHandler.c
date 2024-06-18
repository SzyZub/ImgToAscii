#include "JpegHandler.h"

unsigned char* resize_image(unsigned char* input, int original_width, int original_height, int channels) {
    double aspect_ratio = (double)original_width / original_height;
    int new_width, new_height;
    if (original_width > DISP_W || original_height > DISP_H) {
        if ((double)DISP_W / DISP_H > aspect_ratio) {
            new_width = (int)(DISP_H * aspect_ratio);
            new_height = DISP_H;
        }
        else {
            new_width = DISP_W;
            new_height = (int)(DISP_W / aspect_ratio);
        }
    }
    else {
        new_width = original_width;
        new_height = original_height;
    }
    unsigned char* resized_image = (unsigned char*)malloc(new_width * new_height * channels);
    if (!resized_image) {
        fprintf(stderr, "Failed to allocate memory for resized image\n");
        return NULL;
    }

    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            int src_x = x * original_width / new_width;
            int src_y = y * original_height / new_height;
            for (int c = 0; c < channels; c++) {
                resized_image[(y * (new_width) + x) * channels + c] = input[(src_y * original_width + src_x) * channels + c];
            }
        }
    }
    return resized_image;
}

unsigned char* load_jpeg_file(int *width, int* height, int *channels) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    unsigned char* rowBuffer[1];
    FILE* infile = fopen("ImageFolder/image.jpg", "rb");
    if (!infile) {
        fprintf(stderr, "Error opening file, it isn't put into the imageFolder, has a wrong format or doesn't have a 'image' name");
        return NULL;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    *width = cinfo.output_width;
    *height = cinfo.output_height;
    *channels = cinfo.num_components;

    unsigned long long buff = (*width) * (*height) * 3;
    unsigned char* data = (unsigned char*) malloc(sizeof(unsigned char) * buff);
    rowBuffer[0] = (unsigned char*)(&data[0]);
    jpeg_read_scanlines(&cinfo, &rowBuffer, cinfo.output_height);
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);

    return data;
}
