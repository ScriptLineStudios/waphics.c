#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
EM_JS(int, get_key, (int code), {
    return Module[code] == 1;
});
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "include/external/stbi_image.h"


#ifndef WAPHICS_H_
#define WAPHICS_H_
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
    int x, y;
} Vector2;

typedef struct {
    unsigned int width, height;
    uint32_t *pixels;
} Surface;

Rectangle waphics_rectangle_new(int x, int y, int width, int height);
Circle waphics_circle_new(int x, int y, int radius);
Surface waphics_surface_new(uint32_t *pixels, unsigned int width, unsigned int height);
Surface waphics_surface_from_file(const char *filename);
Vector2 waphics_vector2_new(int x, int y);

void waphics_fill_display(Surface display, uint32_t color);
void waphics_draw_rect(Surface display, Rectangle rect, uint32_t color);
void waphics_draw_line(Surface display, int x1, int y1, int x2, int y2, int color);
void waphics_draw_circle(Surface display, Circle circle, uint32_t color);
void waphics_draw_triangle(Surface display, Vector2 p1, Vector2 p2, Vector2 p3, uint32_t color);
void waphics_draw_triangle_3(Surface display, Vector2 p1, Vector2 p2, Vector2 p3, uint32_t color1, uint32_t color2, uint32_t color3);
void waphics_draw_image(Surface display, Vector2 position, Surface image);
void waphics_draw_image_alpha(Surface display, Rectangle rect,
        uint32_t scale, uint32_t *pixels, uint32_t alpha);
uint32_t waphics_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t waphics_rgb(uint32_t r, uint32_t g, uint32_t b);
int waphics_collide_rect(Rectangle *rect1, Rectangle *rect2);

#define RECT(x, y, w, h) waphics_rectangle_new(x, y, w, h)
#define CIRCLE(x, y, r) waphics_circle_new(x, y, r)
#define VECTOR2(x, y) waphics_vector2_new(x, y)

#define SURFACE(pixels, w, h) waphics_surface_new(pixels, w, h)

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

Vector2 waphics_vector2_new(int x, int y) {
    Vector2 vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

Surface waphics_surface_new(uint32_t *pixels, unsigned int width, unsigned int height) {
    Surface display = {.width=width,  .height=height, .pixels=pixels};
    return display;
}

Surface waphics_surface_from_file(const char *filename) {
    int width, height, channels;
    uint32_t *pixels = (uint32_t *)stbi_load(filename, &width, &height, &channels, 0);
    return waphics_surface_new(pixels, width, height);
}

int waphics_collide_rect(Rectangle *rect1, Rectangle *rect2) {
   if (rect1->x < rect2->x + rect2->w && rect1->x + rect1->w > rect2->x && rect1->y < rect2->y + rect2->h &&
      rect1->y + rect1->h > rect2->y) {
        return 1;         
    }  
    return 0;
}

void waphics_fill_display(Surface display, uint32_t color) {
    for (unsigned int x = 0; x < display.width; x++) {
        for (unsigned int y = 0; y < display.height; y++) {
            display.pixels[y * display.width + x] = color;
        }
    }
}   

void waphics_draw_rect(Surface display, Rectangle rect, uint32_t color) {
    for (int _y = rect.y; _y < rect.h+rect.y; _y++) {
        for (int _x = rect.x; _x < rect.w+rect.x; _x++) {
            if (_x < display.width && _x > 0 && _y < display.height && _y > 0) {
                display.pixels[_y * display.width + _x] = color;
            }
        }
    }
}   

void waphics_draw_line(Surface display, int x1, int y1, int x2, int y2, int color) {
    //behold the worlds worst line rendering algorithm
    double m = ((float)y2 - (float)y1) / (((float)x2 - (float)x1)+0.0000000001);
    double c = (float)y1 - m * (float)x1;
    
    for (int i = 0; i <= display.width * display.height; i++) {
        float x = i % display.width;
        float y = i / display.width;
        if (m > 0) {
            if (x >= x1 && y >= y1 && x <= x2 && y <= y2) {
                if (y - (m * x + c) < m*2 && y - (m * x + c) > -m*2) {
                    display.pixels[(int)y * display.width + (int)x] = color;
                }
            }

            if (x <= x1 && y <= y1 && y >= y2 && x >= x2) {
                if (y - (m * x + c) < m*2 && y - (m * x + c) > -m*2) {
                    display.pixels[(int)y * display.width + (int)x] = color;
                }
            }
        }
        else {
            if (x <= x1 && y >= y1 && y <= y2 && x >= x2) {
                if (y - (m * x + c) > m*2 && y - (m * x + c) < -m*2) {
                    display.pixels[(int)y * display.width + (int)x] = color;
                }
            }

            if (y <= y1 && x >= x1 && x <= x2) {
                if (y - (m * x + c) > m*2 && y - (m * x + c) < -m*2) {
                    display.pixels[(int)y * display.width + (int)x] = color;
                }
            }
        }
    }   
}

float dist(int x1, int y1, int x2, int y2) {
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void waphics_draw_circle(Surface display, Circle circle, uint32_t color) {
    for (int w = circle.x - circle.r; w < circle.x + circle.r; w++) {
        for (int h = circle.y - circle.r; h < circle.y + circle.r; h++) {
            if (circle.x < display.width && circle.x > 0 && circle.y < display.height && circle.y > 0) {
                if (dist((int)circle.x, (int)circle.y, (int)w, (int)h) < circle.r) {
                    display.pixels[(int)h * display.width + (int)w] = color;
                }
            }
        }
    }
}

uint8_t max(uint8_t n1, uint8_t n2) {
    if (n1 >= n2) return n1;
    return n1;
}

uint32_t mix_colors_triangle(uint32_t color1, uint32_t color2, uint32_t color3, float strength1, float strength2, float strength3) {
    uint8_t red = (strength1 * RED(color1) + strength2 * RED(color2) + strength3 * RED(color3)) / (strength1 + strength2 + strength3);
    uint8_t green = (strength1 * GREEN(color1) + strength2 * GREEN(color2) + strength3 * GREEN(color3)) / (strength1 + strength2 + strength3);
    uint8_t blue = (strength1 * BLUE(color1) + strength2 * BLUE(color2) + strength3 * BLUE(color3)) / (strength1 + strength2 + strength3);

    return RGB(red, green, blue);
}

void swap(Vector2 *x, Vector2 *y) {
    Vector2 *tmp;
    tmp = x;
    *x = *y;
    *y = *tmp;
}

void waphics_draw_triangle_3(Surface display, Vector2 p1, Vector2 p2, Vector2 p3, uint32_t color1, uint32_t color2, uint32_t color3) {
    Vector2 op1 = p1;
    Vector2 op2 = p2;
    Vector2 op3 = p3;

    if (p2.y < p1.y) {
       swap(&p1, &p2);
    }
 
    if (p3.y < p2.y) {
       swap(&p2, &p3);
       if (p2.y < p1.y)
          swap(&p2, &p1);
    }
    
    int xs = p1.x;
    int ys = p1.y; 

    int xm = p2.x;
    int ym = p2.y; 

    int xe = p3.x;
    int ye = p3.y; 
    
    float s1 = (xe - xs) / ((ye - ys) + 0.000000000001);
    float s2 = (xm - xs) / ((ym - ys) + 0.000000000001);
    float s3 = (xe - xm) / ((ye - ym) + 0.000000000001);
    for (int y = ys; y < ye; y++) {
        int x1 = xs + (int)((y - ys) * s1);

        int x2;
        if (y < ym)
            x2 = xs + (int)((y - ys) * s2);
        else 
            x2 = xm + (int)((y - ym) * s3);
        
        if (x1 > x2) {
            int tmp = x1;
            x1 = x2;
            x2 = tmp;
        }

        for (int x = x1; x < x2; x++) {
            float denom = ((op2.y - op3.y) * (op1.x - op3.x) + (op3.x - op2.x) * (op1.y - op3.y));
            float barya = ((op2.y - op3.y) * (x - op3.x) + (op3.x - op2.x) * (y - op3.y)) / denom;
            float baryb = ((op3.y - op1.y) * (x - op3.x) + (op1.x - op3.x) * (y - op3.y)) / denom;
            float baryc = 1 - barya - baryb;
            if (x <= display.width && x >= 0) {
                if (y <= display.height && y >= 0) {
                    display.pixels[y * display.width + x] = mix_colors_triangle(color1, color2, color3, barya, baryb, baryc);
                }
            }
        }   
    }
}   

void waphics_draw_triangle(Surface display, Vector2 p1, Vector2 p2, Vector2 p3, uint32_t color) {
    if (p2.y < p1.y) {
       swap(&p1, &p2);
    }
 
    if (p3.y < p2.y) {
       swap(&p2, &p3);
       if (p2.y < p1.y)
          swap(&p2, &p1);
    }
    
    int xs = p1.x;
    int ys = p1.y; 

    int xm = p2.x;
    int ym = p2.y; 

    int xe = p3.x;
    int ye = p3.y; 
    
    float s1 = (xe - xs) / ((ye - ys) + 0.000000000001);
    float s2 = (xm - xs) / ((ym - ys) + 0.000000000001);
    float s3 = (xe - xm) / ((ye - ym) + 0.000000000001);

    for (int y = ys; y < ye; y++) {
        int x1 = xs + (int)((y - ys) * s1);

        int x2;
        if (y < ym)
            x2 = xs + (int)((y - ys) * s2);
        else 
            x2 = xm + (int)((y - ym) * s3);
        
        if (x1 > x2) {
            int tmp = x1;
            x1 = x2;
            x2 = tmp;
        }

        for (int x = x1; x < x2; x++) {
            if (x <= display.width && x >= 0) {
                if (y <= display.height && y >= 0) {
                    display.pixels[y * display.width + x] = color;
                }
            }
        }
    }
}   

float lerp(uint32_t v0, uint32_t v1, float t) {
    return (1 - t) * v0 + t * v1;
}

void waphics_draw_image(Surface display, Vector2 position, Surface image) {
    for (int _y = 0; _y < image.height; _y++) {
        for (int _x = 0; _x < image.width; _x++) {
            uint32_t pixel = image.pixels[_y * image.width + _x];
            display.pixels[(_y+position.y) * display.width + (_x + position.x)] = pixel;
        }
    }
}
// void waphics_draw_image(Surface display, Rectangle rect,
//         uint32_t scale, uint32_t *pixels) {
//     for (int _y = 0; _y < rect.h*scale; _y++) {
//         for (int _x = 0; _x < rect.w*scale; _x++) {
//             if (_x < display.width && _x > 0 && _y < display.height && _y > 0) {
//                 printf("%d\n", _y + rect.y);
//                 if (_y + rect.y > 0) {
//                     uint32_t pixel = pixels[(_y/scale * rect.w + _x/scale)];
//                     uint32_t bg_pixel = display.pixels[(_y+rect.y) * display.width + (_x+rect.x)];

//                     uint8_t red = lerp(RED(bg_pixel), RED(pixel), (float)ALPHA(pixel)/255);
//                     uint8_t green = lerp(GREEN(bg_pixel), GREEN(pixel), (float)ALPHA(pixel)/255);
//                     uint8_t blue = lerp(BLUE(bg_pixel), BLUE(pixel), (float)ALPHA(pixel)/255);
//                     uint8_t alpha = lerp(ALPHA(bg_pixel), ALPHA(pixel), (float)ALPHA(pixel)/255);
//                     if ((_y+rect.y) * display.width + (_x+rect.x) < display.width * display.height) {
//                         // printf("x = %d y = %d\n", _x + rect.x, _y + rect.y);
//                         if (_y + rect.y > 0) {
//                             display.pixels[(_y+rect.y) * display.width + (_x+rect.x)] = RGBA(red, green, blue, alpha);
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

void waphics_draw_image_alpha(Surface display, Rectangle rect,
        uint32_t scale, uint32_t *pixels, uint32_t alpha) {
    if (alpha > 255) alpha = 255;
    for (int _y = 0; _y < rect.h*scale; _y++) {
        for (int _x = 0; _x < rect.w*scale; _x++) {
            if (_x < display.width && _x > 0 && _y < display.height && _y > 0) {
                uint32_t pixel = pixels[(_y/scale * rect.w + _x/scale)];
                uint32_t bg_pixel = display.pixels[(_y+rect.y) * display.width + (_x+rect.x)];

                uint8_t red = lerp(RED(bg_pixel), RED(pixel), (float)alpha/255);
                uint8_t green = lerp(GREEN(bg_pixel), GREEN(pixel), (float)alpha/255);
                uint8_t blue = lerp(BLUE(bg_pixel), BLUE(pixel), (float)alpha/255);
                uint8_t alpha = lerp(ALPHA(bg_pixel), ALPHA(pixel), (float)alpha/255);
                display.pixels[(_y+rect.y) * display.width + (_x+rect.x)] = RGBA(red, green, blue, alpha);
            }
        }
    }
}
#endif