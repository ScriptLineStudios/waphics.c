#define STB_IMAGE_IMPLEMENTATION
#include "src/include/external/stbi_image.h"

int main() {
    int width, height, channels;
    uint32_t *pixels = (uint32_t *)stbi_load("/home/scriptline/programming/C/assets/block1.png" , &width, &height, &channels, 0);
    printf("%p\n", pixels);
    return 0;
}