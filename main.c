#define WAPHICS_IMPLEMENTATION
#include "src/waphics.c"

uint32_t pixels[1000 * 600];
Screen screen;

#define WIDTH 1000
#define HEIGHT 600

void init(void) {
    screen = SCREEN(pixels, WIDTH, HEIGHT);
}

static int x;

uint32_t *run(void) {
    waphics_fill_screen(screen, 0xFFFFFFFF);
    waphics_draw_triangle(screen, x, 100, 
                                  200, 200, 
                                  150, 200, 
                                  0xFF0000FF, 0xFF00FF00, 0xFFFF0000);

    if (get_key(KEY_D)) x+=10;
    if (get_key(KEY_A)) x-=10;


    return screen.pixels;
}

