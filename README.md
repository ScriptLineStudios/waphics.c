# waphics.c - WebAssembly Graphics
## A web browser based video game library for C.

Waphics allows you to easily create video games in C and export them to the web browser. Waphics provides a Javascript runtime enviroment for your C code which allows for:

<ul>
  <li>Keyboard input (mouse input to come)</li>
  <li>Playing sounds</li>
  <li>Rendering primitimes (circles, rectangles, triangles)</li>
  <li>Image rendering</li>
  <li>Alpha blending</li>
</ul>

```C
#define WAPHICS_IMPLEMENTATION
#include "src/waphics.c"

#include "assets/block.h"

#define WIDTH 1000
#define HEIGHT 600

uint32_t pixels[WIDTH * HEIGHT];
Surface display;

void init(void) {
    display = SCREEN(pixels, WIDTH, HEIGHT);
}

static int x;

uint32_t *run(void) {
    //fill the display with black
    waphics_fill_display(display, RGB(0, 0, 0));
    //draw a red rectangle
    waphics_draw_rect(display, RECT(0, 0, 50, 50), RGB(255, 0, 0));
    //draw a blue circle
    waphics_draw_circle(display, CIRCLE(100, 100, 50), RGB(0, 100, 100));
    //draw an image
    waphics_draw_image(display, RECT(x, 0, 16, 16), 10, block_pixels);

    if (get_key(KEY_D)) x+=10;
    if (get_key(KEY_A)) x-=10;


    return display.pixels;
}
```

# Examples

![Peek 2023-02-12 11-56](https://user-images.githubusercontent.com/85095943/218304377-a63e7635-d910-407b-86c9-5a90035aadac.gif)
Triangle with mouse input.

![Peek 2023-02-12 12-07](https://user-images.githubusercontent.com/85095943/218304809-1dea99ef-9ea0-415a-ad4b-c9cf9d3096ff.gif)

Image loading with alpha.

# Using the Library
## Building from source
```bash
 1. git clone https://github.com/ScriptLineStudios/waphics.c
 2. cd waphics.c
 3. sudo make DESTDIR=/usr/bin/ install
```

# Getting started
Waphics is simple to use. Once installed simply create a new C file and add an init and run method as follows:

```C
#define WAPHICS_IMPLEMENTATION
#include "waphics.c"

#define WIDTH 1000
#define HEIGHT 600

uint32_t pixels[WIDTH * HEIGHT];
Surface display;

void init(void) {
    display = SCREEN(pixels, WIDTH, HEIGHT);
}

uint32_t *run(void) {
  // your code will go here...
  
  return display.pixels;
}
```

From there you are free to use waphics functionaltiy on the web! Once you are ready to compile to the web. Simpliy run:
```bash
waphics <your_file>.c <width> <height>
```

This will generate the following:
```
index.html
output.wasm
javascript.js
```

Simpliy run index.html using a web server of your choice, and you will be greeted by your window!

# Keyboard Inputs
```C
if get_key(KEY_A) {
  // the code here will only run when A is pressed
}
```
