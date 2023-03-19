#define WAPHICS_IMPLEMENTATION
#include "../src/waphics.c"

#include "player.c"

uint32_t pixels[1000 * 600];
Screen screen;

#define WIDTH 1000
#define HEIGHT 600

Player player;
Tilemap tilemap;

void init(void) {
    screen = SCREEN(pixels, WIDTH, HEIGHT);
    player.rect = RECT(10, 10, 40, 40);
    player.color = 0xFF0000FF;
    player.speed = 2;

    tilemap.num_tiles = 4;
    tilemap.tiles[0] = RECT(48, 200, 48, 48);
    tilemap.tiles[1] = RECT(48*2, 200, 48, 48);
    tilemap.tiles[2] = RECT(48*3, 200, 48, 48);
    tilemap.tiles[3] = RECT(48*4, 200, 48, 48);
}

static int x;

uint32_t *render(void) {
    waphics_fill_screen(screen, 0xFF000000);
    test();
    player_update(screen, &player, &tilemap);

    return screen.pixels;
}

