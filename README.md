# waphics.c - WebAssembly Graphics
## A web browser based video game library for C.

Waphics allows you to easily create video games in C and export them to the web browser.

```C
#define WAPHICS_IMPLEMENTATION
#include "src/waphics.c"

uint32_t pixels[1000 * 600];
Screen screen;

void init(void) {
    screen = SCREEN(pixels, 1000, 600);
}

uint32_t *run(void) {
    //fill the screen with black
    waphics_fill_screen(screen, RGB(0, 0, 0));
    //draw a red rectangle
    waphics_draw_rect(screen, RECT(0, 0, 50, 50), RGB(255, 0, 0));
    //draw a blue circle
    waphics_draw_circle(screen, CIRCLE(100, 100, 50), RGB(0, 100, 100));

    return screen.pixels;
}
```
