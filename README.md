# waphics.c - WebAssembly Graphics
## A web browser based video game library for C.

Waphics allows you to easily create video games in C and export them to the web browser.

```C
#include "renderer.c"

uint32_t pixels[1000 * 600];
Screen screen;

void init(void) {
    screen = renderer_init(pixels, 1000, 600);
}

uint32_t *run(void) {
    fill_screen(screen, 0xFF090909);
    draw_rect(screen, rectangle_new(0, x, 50, 50), 0xFFFF00FF);
    return pixels;
}

```
