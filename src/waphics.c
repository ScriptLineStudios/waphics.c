#include <stdint.h>

#ifndef WAPHICS_H_
#define WAPHICS_H_
extern int get_key(int key_code);
extern uint32_t jfloor(int); 
extern double jsqrt(int); 
extern void jprint(float); 
extern float jabs(float); 
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

#define RECT(x, y, w, h) waphics_rectangle_new(x, y, w, h)
#define CIRCLE(x, y, r) waphics_rectangle_new(x, y, r)
#define SCREEN(pixels, w, h) waphics_screen_new(pixels, w, h)

#endif

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

int dist(int x1, int y1, int x2, int y2) {
    return (jsqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) + 1) / 1;
}

void waphics_draw_circle(Screen screen, Circle circle, uint32_t color) {
    for (int i = 0; i <= screen.width * screen.height; i++) {
        float _x = i % screen.width;
        float _y = i / screen.width;

        if (dist((int)circle.x, (int)circle.y, (int)_x, (int)_y) < circle.r) {
            screen.pixels[(int)_y * screen.width + (int)_x] = color;
        }
    }
}

#define RED(color)   (((color)&0x000000FF)>>(8*0))
#define GREEN(color) (((color)&0x0000FF00)>>(8*1))
#define BLUE(color)  (((color)&0x00FF0000)>>(8*2))
#define ALPHA(color) (((color)&0xFF000000)>>(8*3))
#define RGBA(r, g, b, a) ((((r)&0xFF)<<(8*0)) | (((g)&0xFF)<<(8*1)) | (((b)&0xFF)<<(8*2)) | (((a)&0xFF)<<(8*3)))

uint8_t max(uint8_t n1, uint8_t n2) {
    if (n1 >= n2) return n1;
    return n1;
}

uint32_t mix_colors_triangle(uint32_t color1, uint32_t color2, uint32_t color3, uint32_t strength1, uint32_t strength2, uint32_t strength3, float area) {
    uint8_t red1 = RED(color1);
    uint8_t green1 = GREEN(color1);
    uint8_t blue1 = BLUE(color1);
    uint8_t alpha1 = ALPHA(color1);

    uint8_t red2 = RED(color2);
    uint8_t green2 = GREEN(color2);
    uint8_t blue2 = BLUE(color2);
    uint8_t alpha2 = ALPHA(color2);

    uint8_t red3 = RED(color3);
    uint8_t green3 = GREEN(color3);
    uint8_t blue3 = BLUE(color3);
    uint8_t alpha3 = ALPHA(color3);

    return color1;

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
    float area = jabs(( x2-x1)*(y3-y1) - (x3-x1)*(y2-y1) );
    for (int i = 0; i <= screen.width * screen.height; i++) {
        float px = i % screen.width;
        float py = i / screen.width;

        float area1 =    jabs( (x1-px)*(y2-py) - (x2-px)*(y1-py) );
        float area2 =    jabs( (x2-px)*(y3-py) - (x3-px)*(y2-py) );
        float area3 =    jabs( (x3-px)*(y1-py) - (x1-px)*(y3-py) );
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
            uint32_t pixel = pixels[(_y/scale * rect.w + _x/scale)];
            uint32_t bg_pixel = screen.pixels[(_y+rect.y) * screen.width + (_x+rect.x)];

            uint8_t red = lerp(RED(bg_pixel), RED(pixel), (float)ALPHA(pixel)/255);
            uint8_t green = lerp(GREEN(bg_pixel), GREEN(pixel), (float)ALPHA(pixel)/255);
            uint8_t blue = lerp(BLUE(bg_pixel), BLUE(pixel), (float)ALPHA(pixel)/255);
            uint8_t alpha = lerp(ALPHA(bg_pixel), ALPHA(pixel), (float)ALPHA(pixel)/255);
            if (_x < screen.width && _x > 0 && _y < screen.height && _y > 0) {
                screen.pixels[(_y+rect.y) * screen.width + (_x+rect.x)] = RGBA(red, green, blue, alpha);
            }
        }
    }
}

void waphics_draw_image_alpha(Screen screen, Rectangle rect,
        uint32_t scale, uint32_t *pixels, uint32_t alpha) {
    for (int _y = 0; _y < rect.h*scale; _y++) {
        for (int _x = 0; _x < rect.w*scale; _x++) {
            uint32_t pixel = pixels[(_y/scale * rect.w + _x/scale)];
            uint32_t bg_pixel = screen.pixels[(_y+rect.y) * screen.width + (_x+rect.x)];

            uint8_t red = lerp(RED(bg_pixel), RED(pixel), (float)alpha/255);
            uint8_t green = lerp(GREEN(bg_pixel), GREEN(pixel), (float)alpha/255);
            uint8_t blue = lerp(BLUE(bg_pixel), BLUE(pixel), (float)alpha/255);
            uint8_t alpha = lerp(ALPHA(bg_pixel), ALPHA(pixel), (float)alpha/255);
            if (_x < screen.width && _x > 0 && _y < screen.height && _y > 0) {
                screen.pixels[(_y+rect.y) * screen.width + (_x+rect.x)] = RGBA(red, green, blue, alpha);
            }
        }
    }
}