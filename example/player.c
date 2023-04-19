#include "../assets/block.h"

typedef struct {
    Rectangle rect;
    uint32_t color;
    int speed;
    int movement[2];
    float camera[2];
} Player;

typedef struct {
    Rectangle rect;
} Tile;

typedef struct {
    int num_tiles;
    Rectangle tiles[4];
} Tilemap;

void player_move(Screen screen, Player *player, Tilemap *tilemap) {
    player->rect.x += player->movement[0];
    for (int i = 0; i < tilemap->num_tiles; i++) {
        Rectangle tile = tilemap->tiles[i];
        if (waphics_collide_rect(&player->rect, &tile)) {
            if (player->movement[0] > 0) {
                player->rect.x = tile.x-player->rect.w;
            }
            else if (player->movement[0] < 0) {
                player->rect.x = tile.x+tile.w;
            }
        }
    }
    player->rect.y += player->movement[1];  
    for (int i = 0; i < tilemap->num_tiles; i++) {
        Rectangle tile = tilemap->tiles[i];
        if (waphics_collide_rect(&player->rect, &tile)) {
            if (player->movement[1] > 0) {
                player->rect.y = tile.y-player->rect.h;
            }
            else if (player->movement[1] < 0) {
                player->rect.y = tile.y+player->rect.h;
            }
        }
    }
}

void player_update(Screen screen, Player *player, Tilemap *tilemap) {
    waphics_draw_rect(screen, RECT(player->rect.x - player->camera[0], player->rect.y - player->camera[1], player->rect.w, player->rect.h), player->color);

    player->movement[0] = 0;
    player->movement[1] = 0;

    player->camera[0] += (player->rect.x - player->camera[0]) / 7 - 50;
    player->camera[1] += (player->rect.y - player->camera[1]) / 7 - 50;

    player->movement[0]++;

    if (get_key(KEY_D)) player->movement[0] += player->speed;
    if (get_key(KEY_A)) player->movement[0] -= player->speed;
    if (get_key(KEY_SPACE)) player->movement[1] -= player->speed*10;

    waphics_draw_image(screen, RECT(0, 0, block_width, block_height), 3, block_pixels);
    player->movement[1]+=4;
    // for (int i = 0; i < tilemap->num_tiles; i++) {
        // Rectangle tile = tilemap->tiles[i];
        // waphics_draw_image(screen, RECT(tile.x - player->camera[0], tile.y - player->camera[1], block_width, block_height), 3, block_pixels);
        // waphics_draw_rect(screen, RECT(tile.x - player->camera[0], tile.y - player->camera[1], tile.w, tile.h), 0xFFFF0000);
    // }

    player_move(screen, player, tilemap);
}