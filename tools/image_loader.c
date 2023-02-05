#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stbi_image.h"

int main(int argc, char **argv) {
    assert(argc == 3);
    int w, h, c;
    int original_length = strlen(argv[2]);
    uint32_t *pixels = (uint32_t*)stbi_load(argv[1], &w, &h, &c, 0);
    const char *tmp = strcat(argv[2], ".h");
    FILE *f = fopen(tmp, "w");
    fprintf(f, "#include <stdint.h>\n");
    argv[2][original_length] = '\0';
    fprintf(f, "int %s_width = %d;\n", argv[2], w);
    fprintf(f, "int %s_height = %d;\n", argv[2], h);
    fprintf(f, "uint32_t %s_pixels[] = {", argv[2]);
    for (int i = 0; i < w * h; i++) {
        fprintf(f, "0x%04x,", pixels[i]);
        if (i % 7 == 0) fprintf(f, "\n");
    }
    fprintf(f, "};");

    fclose(f);
    return 0;
}