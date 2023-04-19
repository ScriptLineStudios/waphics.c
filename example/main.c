#define WAPHICS_IMPLEMENTATION
#include "../src/waphics.c"

#include "../assets/block.h"

uint32_t pixels[1000 * 600];
Screen screen;

#define WIDTH 1000
#define HEIGHT 600

void init(void) {
    screen = SCREEN(pixels, WIDTH, HEIGHT);
}

static int x;

uint32_t *render(void) {
    waphics_fill_screen(screen, 0xFF000000);
    
    waphics_draw_image(screen, RECT(0, x, block_width, block_height), 3, block_pixels);
    x--;
    return screen.pixels;
}

