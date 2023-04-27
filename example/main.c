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
static int y;

void init(void) {
    display = waphics_surface_new(pixels, WIDTH, HEIGHT);
    image = waphics_surface_from_file("assets/images/block1.png");
}

uint32_t *render(void) {
    waphics_fill_display(display, 0xFF000000);
    Surface new = waphics_surface_scale(&image, VECTOR2(135+x, 64));
    waphics_draw_image(display, VECTOR2(x, y), new);

    if (get_key(KEY_D)) {
        x++;
    }
    if (get_key(KEY_A)) {
        x--;
    }
    if (get_key(KEY_S)) {
        y++;
    }
    if (get_key(KEY_W)) {
        y--;
    }

    return display.pixels;
}