# waphics.c - WebAssembly Graphics
## A web browser based video game library for C.

Waphics allows you to easily create video games in C and export them to the web browser. Waphics provides a Javascript runtime enviroment for your C code which allows for:

<ul>
  <li>User input (keyboard and mouse)</li>
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
Screen screen;

void init(void) {
    screen = SCREEN(pixels, WIDTH, HEIGHT);
}

static int x;

uint32_t *run(void) {
    //fill the screen with black
    waphics_fill_screen(screen, RGB(0, 0, 0));
    //draw a red rectangle
    waphics_draw_rect(screen, RECT(0, 0, 50, 50), RGB(255, 0, 0));
    //draw a blue circle
    waphics_draw_circle(screen, CIRCLE(100, 100, 50), RGB(0, 100, 100));
    //draw an image
    waphics_draw_image(screen, RECT(x, 0, 16, 16), 10, block_pixels);

    if (get_key(KEY_D)) x+=10;
    if (get_key(KEY_A)) x-=10;


    return screen.pixels;
}
```

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
Screen screen;

void init(void) {
    screen = SCREEN(pixels, WIDTH, HEIGHT);
}

uint32_t *run(void) {
  // your code will go here...
  
  return screen.pixels;
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
```

Simpliy run index.html using a web server of your choice, and you will be greeted by your window!

# Using Images
In order to use images on the web. You must first generate the bytes of the images this can be done with the built in waphics tool:

```bash
waphics_image_load <image_path>.png <image_name>
```

This will generate:
```
<image_name>.h
```

This header file contains all the information needed to used the image on the web!
```C
// other include
#include "<image_name>.h"

uint32_t *run(void) {
  // other code
  
  //void waphics_draw_image(Screen screen, Rectangle rect, uint32_t scale, uint32_t *pixels);
  waphics_draw_image(screen, RECT(xpos, ypos, <image_name>_width, <image_name>_height), 1, <image_name>_pixels);
    
  return screen.pixels;
}
```

# Keyboard Inputs
```C
if get_key(KEY_A) {
  // the code here will only run when A is pressed
}
```
