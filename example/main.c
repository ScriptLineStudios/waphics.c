#define WAPHICS_IMPLEMENTATION
#include "../src/waphics.c"

#include <math.h>

uint32_t pixels[1000 * 600];

Surface display;
Surface image;
int x = 0;

#define WIDTH 1000
#define HEIGHT 600

void init(void) {
    display = waphics_surface_new(pixels, WIDTH, HEIGHT);
    image = waphics_surface_from_file("assets/images/block1.png");
    image = waphics_surface_scale(&image, VECTOR2(100, 300));
}

uint32_t *render(void) {
    waphics_fill_display(display, 0xFF000000);

    if (get_key(KEY_D)) {
        x++;
    }
    if (get_key(KEY_A)) {
        x--;
    }

    // waphics_draw_triangle_3(display, VECTOR2(10, 10 + (0 * 100)), VECTOR2(300, 10), VECTOR2(25, 300), RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255));
    
    waphics_draw_triangle_3(display, VECTOR2(200, 200), VECTOR2(-100, 300), VECTOR2(400, 300 - x), RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255));
    
    // waphics_draw_image(display, VECTOR2(x, 0), image);

    return display.pixels;
}