#define WAPHICS_IMPLEMENTATION
#include "../src/waphics.c"

#include "../assets/block.h"

#include <math.h>

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
    
    waphics_draw_triangle_3(screen, VECTOR2(10+x, 10), VECTOR2(200, 100), VECTOR2(100, 200), RGB(255, 0, x), RGB(x, 255, 0), RGB(0, x, 255));
    x++;
    return screen.pixels;
}

