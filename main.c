#define WAPHICS_IMPLEMENTATION
#include "src/waphics.c"

#include "assets/block.h"

uint32_t pixels[1000 * 600];
Screen screen;

#define WIDTH 1000
#define HEIGHT 600

void init(void) {
    screen = SCREEN(pixels, WIDTH, HEIGHT);
}

static int x;

uint32_t *run(void) {
    //fill the screen with black
    waphics_fill_screen(screen, RGB(0, 0, 0));
    //draw a red rectangle
    waphics_draw_rect(screen, RECT(0, 0, 50, 50), RGB(255, 0, 0));
    //draw a blue circle
    waphics_draw_circle(screen, CIRCLE(100, 100, 50), RGB(0, 100, 100));
    //draw an image
    waphics_draw_image(screen, RECT(x, 0, 16, 16), 10, block_pixels);

    if (get_key(KEY_D)) x+=10;
    if (get_key(KEY_A)) x-=10;


    return screen.pixels;
}

