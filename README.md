# waphics.c - WebAssembly Graphics
## A web browser based video game library for C.

Waphics allows you to easily create video games in C and export them to the web browser. Waphics provides a Javascript runtime enviroment for your C code which allows for:

<ul>
  <li>User input (keyboard and mouse)</li>
  <li>Playing sounds</li>
  <li>Third item</li>
  <li>Fourth item</li>
</ul>

```C
#define WAPHICS_IMPLEMENTATION
#include "src/waphics.c"

uint32_t pixels[1000 * 600];
Screen screen;

#define WIDTH 1000
#define HEIGHT 600

void init(void) {
    screen = SCREEN(pixels, WIDTH, HEIGHT);
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

# Using the Library
## Building from source
```
 1. git clone https://github.com/ScriptLineStudios/waphics.c
 2. cd waphics.c
 3. sudo make DESTDIR=/usr/bin/ install
```

# Getting started
Waphics is simple to use. Once installed simply create a new C file and add an init and run method as follows:

```C
void init(void) {
    
}


```
