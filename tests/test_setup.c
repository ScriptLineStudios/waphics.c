#include <stdbool.h>

#define WAPHICS_IMPLEMENTATION
#include "../src/waphics.c"

void test_keys() {
    assert(KEY_A == 65);
}

void test_rect() {
    uint32_t pixels[10 * 10];
    Surface surf = waphics_surface_new(pixels, 10, 10);
    assert(*surf.pixels == *pixels);
    uint32_t color = RGB(255, 0, 0);
    assert(color == 0xFF0000FF);
    waphics_draw_rect(surf, RECT(0, 0, 4, 4), color);
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            assert(surf.pixels[y * 10 + x] == color);
        }
    }
}

int main() {
    test_keys();
    test_rect();
}