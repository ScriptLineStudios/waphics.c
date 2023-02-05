#include "src/waphics.c"

uint32_t pixels[1000 * 600];
Screen screen;

void init(void) {
    screen = SCREEN(pixels, 1000, 600);
}

uint32_t *run(void) {
    waphics_fill_screen(screen, 0xFF090909);
    waphics_draw_rect(screen, RECT(0, 0, 50, 50), 0xFFFF00FF);
    waphics_draw_rect(screen, RECT(80, 0, 50, 50), 0xFFFF00FF);

    return screen.pixels;
}

