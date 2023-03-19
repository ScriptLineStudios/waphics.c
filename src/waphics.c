#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <emscripten.h>

EM_JS(void, test, (), {
    document.getElementById('canvas').addEventListener('keypress', handleKeyPress);
    function handleKeyPress(e) { 
        console.log(e);    
    }
});

EM_JS(int, get_key, (int key), {
    // var keyCode;
    // console.log("getting key");
    // document.addEventListener(
    //     "keydown",
    //     function(event) {
    //         keyCode = event.keyCode;
    //     },
    // );
    // document.addEventListener(
    //     "keyup",
    //     function(event) {
    //         if (event.keyCode == keyCode) keyCode = null;
    //     },
    // );
    // if (keyCode == key) return 1;
    // return 0;
});

#ifndef WAPHICS_H_
#define WAPHICS_H_
extern int get_key(int key_code);
extern uint32_t jfloor(int); 
extern double jsqrt(int); 
extern void jprint(float); 
extern float jfabsf(float); 
extern float jsin(float); 
extern void play_sound(const char *path); 

#define KEY_A 65
#define KEY_B 66
#define KEY_C 67
#define KEY_D 68
#define KEY_E 69
#define KEY_F 70
#define KEY_G 71
#define KEY_H 72
#define KEY_I 73
#define KEY_J 74
#define KEY_K 75
#define KEY_L 76
#define KEY_M 77
#define KEY_N 78
#define KEY_O 79
#define KEY_P 80
#define KEY_Q 81
#define KEY_R 82
#define KEY_S 83
#define KEY_T 84
#define KEY_U 85
#define KEY_V 86
#define KEY_W 87
#define KEY_X 88
#define KEY_Y 89
#define KEY_Z 90
#define KEY_SPACE 32

#define RED(color)   (((color)&0x000000FF)>>(8*0))
#define GREEN(color) (((color)&0x0000FF00)>>(8*1))
#define BLUE(color)  (((color)&0x00FF0000)>>(8*2))
#define ALPHA(color) (((color)&0xFF000000)>>(8*3))
#define RGBA(r, g, b, a) ((((r)&0xFF)<<(8*0)) | (((g)&0xFF)<<(8*1)) | (((b)&0xFF)<<(8*2)) | (((a)&0xFF)<<(8*3)))
#define RGB(r, g, b) ((((r)&0xFF)<<(8*0)) | (((g)&0xFF)<<(8*1)) | (((b)&0xFF)<<(8*2)) | (((255)&0xFF)<<(8*3)))

typedef struct {
    int x, y, w, h;
} Rectangle;

typedef struct {
    int x, y, r;
} Circle;

typedef struct {
    unsigned int width, height;
    uint32_t *pixels;
} Screen;

Rectangle waphics_rectangle_new(int x, int y, int width, int height);
Circle waphics_circle_new(int x, int y, int radius);
Screen waphics_screen_new(uint32_t *pixels, unsigned int width, unsigned int height);
void waphics_fill_screen(Screen screen, uint32_t color);
void waphics_draw_rect(Screen screen, Rectangle rect, uint32_t color);
void waphics_draw_line(Screen screen, int x1, int y1, int x2, int y2, int color);
void waphics_draw_circle(Screen screen, Circle circle, uint32_t color);
void waphics_draw_triangle(Screen screen, int _x1, int _y1, 
                                  int _x2, int _y2, 
                                  int _x3, int _y3, uint32_t color1, uint32_t color2, uint32_t color3);
void waphics_draw_image(Screen screen, Rectangle rect,
        uint32_t scale, uint32_t *pixels);
void waphics_draw_image_alpha(Screen screen, Rectangle rect,
        uint32_t scale, uint32_t *pixels, uint32_t alpha);
uint32_t waphics_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t waphics_rgb(uint32_t r, uint32_t g, uint32_t b);
int waphics_collide_rect(Rectangle *rect1, Rectangle *rect2);

#define RECT(x, y, w, h) waphics_rectangle_new(x, y, w, h)
#define CIRCLE(x, y, r) waphics_circle_new(x, y, r)
#define SCREEN(pixels, w, h) waphics_screen_new(pixels, w, h)

#endif

#ifdef WAPHICS_IMPLEMENTATION

uint32_t waphics_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return RGBA(r, g, b, a);
}

uint32_t waphics_rgb(uint32_t r, uint32_t g, uint32_t b) {
    return RGBA(r, g, b, 255);
}

Rectangle waphics_rectangle_new(int x, int y, int width, int height) {
    Rectangle rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    return rect;
}

Circle waphics_circle_new(int x, int y, int radius) {
    Circle circ;
    circ.x = x;
    circ.y = y;
    circ.r = radius;
    return circ;
}

Screen waphics_screen_new(uint32_t *pixels, unsigned int width, unsigned int height) {
    Screen screen = {.width=width,  .height=height, .pixels=pixels};
    return screen;
}

int waphics_collide_rect(Rectangle *rect1, Rectangle *rect2) {
   if (rect1->x < rect2->x + rect2->w && rect1->x + rect1->w > rect2->x && rect1->y < rect2->y + rect2->h &&
      rect1->y + rect1->h > rect2->y) {
        return 1;         
    }  
    return 0;
}

void waphics_fill_screen(Screen screen, uint32_t color) {
    for (unsigned int x = 0; x < screen.width; x++) {
        for (unsigned int y = 0; y < screen.height; y++) {
            screen.pixels[y * screen.width + x] = color;
        }
    }
}   

void waphics_draw_rect(Screen screen, Rectangle rect, uint32_t color) {
    for (int _y = rect.y; _y < rect.h+rect.y; _y++) {
        for (int _x = rect.x; _x < rect.w+rect.x; _x++) {
            if (_x < screen.width && _x > 0 && _y < screen.height && _y > 0) {
                screen.pixels[_y * screen.width + _x] = color;
            }
        }
    }
}   

void waphics_draw_line(Screen screen, int x1, int y1, int x2, int y2, int color) {
    //behold the worlds worst line rendering algorithm
    double m = ((float)y2 - (float)y1) / (((float)x2 - (float)x1)+0.0000000001);
    double c = (float)y1 - m * (float)x1;
    
    for (int i = 0; i <= screen.width * screen.height; i++) {
        float x = i % screen.width;
        float y = i / screen.width;
        if (m > 0) {
            if (x >= x1 && y >= y1 && x <= x2 && y <= y2) {
                if (y - (m * x + c) < m*2 && y - (m * x + c) > -m*2) {
                    screen.pixels[(int)y * screen.width + (int)x] = color;
                }
            }

            if (x <= x1 && y <= y1 && y >= y2 && x >= x2) {
                if (y - (m * x + c) < m*2 && y - (m * x + c) > -m*2) {
                    screen.pixels[(int)y * screen.width + (int)x] = color;
                }
            }
        }
        else {
            if (x <= x1 && y >= y1 && y <= y2 && x >= x2) {
                if (y - (m * x + c) > m*2 && y - (m * x + c) < -m*2) {
                    screen.pixels[(int)y * screen.width + (int)x] = color;
                }
            }

            if (y <= y1 && x >= x1 && x <= x2) {
                if (y - (m * x + c) > m*2 && y - (m * x + c) < -m*2) {
                    screen.pixels[(int)y * screen.width + (int)x] = color;
                }
            }
        }
    }   
}

float dist(int x1, int y1, int x2, int y2) {
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void waphics_draw_circle(Screen screen, Circle circle, uint32_t color) {
    for (int w = circle.x - circle.r; w < circle.x + circle.r; w++) {
        for (int h = circle.y - circle.r; h < circle.y + circle.r; h++) {
            if (circle.x < screen.width && circle.x > 0 && circle.y < screen.height && circle.y > 0) {
                if (dist((int)circle.x, (int)circle.y, (int)w, (int)h) < circle.r) {
                    screen.pixels[(int)h * screen.width + (int)w] = color;
                }
            }
        }
    }
}

uint8_t max(uint8_t n1, uint8_t n2) {
    if (n1 >= n2) return n1;
    return n1;
}

uint32_t mix_colors_triangle(uint32_t color1, uint32_t color2, uint32_t color3, float strength1, float strength2, float strength3, float area) {
    uint8_t red1 = RED(color1);
    uint8_t green1 = GREEN(color1);
    uint8_t blue1 = BLUE(color1);

    uint8_t red2 = RED(color2);
    uint8_t green2 = GREEN(color2);
    uint8_t blue2 = BLUE(color2);

    uint8_t red3 = RED(color3);
    uint8_t green3 = GREEN(color3);
    uint8_t blue3 = BLUE(color3);

    if (strength1==0) strength1 = 1;
    if (strength2==0) strength2 = 1;
    if (strength3==0) strength3 = 1;


    float distp1 = 1/strength1;
    float distp2 = 1/strength2;
    float distp3 = 1/strength3;
    
    uint8_t red = (uint8_t)((red1 * distp1 + red2 * distp2 + red3 * distp3) / (distp1 + distp2 + distp3));
    uint8_t green = (uint8_t)((green1 * distp1 + green2 * distp2 + green3 * distp3) / (distp1 + distp2 + distp3));
    uint8_t blue = (uint8_t)((blue1 * distp1 + blue2 * distp2 + blue3 * distp3) / (distp1 + distp2 + distp3));

    return RGB(red, green, blue);
}

void waphics_draw_triangle(Screen screen, int _x1, int _y1, 
                                  int _x2, int _y2, 
                                  int _x3, int _y3, uint32_t color1, uint32_t color2, uint32_t color3) {

    //basically http://jeffreythompson.org/collision-detection/tri-point.php
    float x1 = (float)_x1;
    float y1 = (float)_y1;
    float x2 = (float)_x2;
    float y2 = (float)_y2;
    float x3 = (float)_x3;
    float y3 = (float)_y3;
    float area = fabsf(( x2-x1)*(y3-y1) - (x3-x1)*(y2-y1) );
    for (int i = 0; i <= screen.width * screen.height; i++) {
        float px = i % screen.width;
        float py = i / screen.width;

        float area1 =    fabsf( (x1-px)*(y2-py) - (x2-px)*(y1-py) );
        float area2 =    fabsf( (x2-px)*(y3-py) - (x3-px)*(y2-py) );
        float area3 =    fabsf( (x3-px)*(y1-py) - (x1-px)*(y3-py) );
        if (area1 + area2 + area3 == area) {
            uint32_t mixed_color = mix_colors_triangle(color1, color2, color3, dist(px, py, _x1, _y1), dist(px, py, _x2, _y2), dist(px, py, _x3, _y3), area);
            screen.pixels[(int)py * screen.width + (int)px] = mixed_color;
        }
    }
}

float lerp(uint32_t v0, uint32_t v1, float t) {
  return (1 - t) * v0 + t * v1;
}

void waphics_draw_image(Screen screen, Rectangle rect,
        uint32_t scale, uint32_t *pixels) {
    for (int _y = 0; _y < rect.h*scale; _y++) {
        for (int _x = 0; _x < rect.w*scale; _x++) {
            if (_x < screen.width && _x > 0 && _y < screen.height && _y > 0) {
                uint32_t pixel = pixels[(_y/scale * rect.w + _x/scale)];
                uint32_t bg_pixel = screen.pixels[(_y+rect.y) * screen.width + (_x+rect.x)];

                uint8_t red = lerp(RED(bg_pixel), RED(pixel), (float)ALPHA(pixel)/255);
                uint8_t green = lerp(GREEN(bg_pixel), GREEN(pixel), (float)ALPHA(pixel)/255);
                uint8_t blue = lerp(BLUE(bg_pixel), BLUE(pixel), (float)ALPHA(pixel)/255);
                uint8_t alpha = lerp(ALPHA(bg_pixel), ALPHA(pixel), (float)ALPHA(pixel)/255);
                if ((_y+rect.y) * screen.width + (_x+rect.x) < screen.width * screen.height) {
                    screen.pixels[(_y+rect.y) * screen.width + (_x+rect.x)] = RGBA(red, green, blue, alpha);
                }
            }
        }
    }
}

void waphics_draw_image_alpha(Screen screen, Rectangle rect,
        uint32_t scale, uint32_t *pixels, uint32_t alpha) {
    if (alpha > 255) alpha = 255;
    for (int _y = 0; _y < rect.h*scale; _y++) {
        for (int _x = 0; _x < rect.w*scale; _x++) {
            if (_x < screen.width && _x > 0 && _y < screen.height && _y > 0) {
                uint32_t pixel = pixels[(_y/scale * rect.w + _x/scale)];
                uint32_t bg_pixel = screen.pixels[(_y+rect.y) * screen.width + (_x+rect.x)];

                uint8_t red = lerp(RED(bg_pixel), RED(pixel), (float)alpha/255);
                uint8_t green = lerp(GREEN(bg_pixel), GREEN(pixel), (float)alpha/255);
                uint8_t blue = lerp(BLUE(bg_pixel), BLUE(pixel), (float)alpha/255);
                uint8_t alpha = lerp(ALPHA(bg_pixel), ALPHA(pixel), (float)alpha/255);
                screen.pixels[(_y+rect.y) * screen.width + (_x+rect.x)] = RGBA(red, green, blue, alpha);
            }
        }
    }
}
#endif