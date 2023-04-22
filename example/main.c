#define WAPHICS_IMPLEMENTATION
#include "../src/waphics.c"

#include "../assets/block.h"

#include <math.h>

uint32_t pixels[1000 * 600];

Surface display;
Surface image;

#define WIDTH 1000
#define HEIGHT 600

static int x;

void init(void) {
    display = waphics_surface_new(pixels, WIDTH, HEIGHT);
    image = waphics_surface_from_file("assets/images/block1.png");
}

uint32_t *render(void) {
    waphics_fill_display(display, 0xFF000000);
    // waphics_draw_triangle_3(display, VECTOR2(10+x, 10), VECTOR2(200, 100), VECTOR2(100, 200), RGB(255, 0, x), RGB(x, 255, 0), RGB(0, x, 255));
    waphics_draw_image(display, VECTOR2(100, 100), image);

    if (get_key(KEY_A)) {
        x--;
    }
    if (get_key(KEY_D)) {
        x++;
    }
    
    return display.pixels;
}

