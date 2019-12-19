#include <sega_mth.h>

#include "hurler.h"
#include "../sprite.h"
#include "../player.h"
#include "../print.h"

static const Uint16 hurler_chars[] = {58, 57, 59, 57};
#define VERTICAL_FLASH (60)
#define HORIZONTAL_FLASH (61)
#define HURLER_ANIMTIME (10)
#define HURLER_SPEED (MTH_FIXED(0.8))
#define FLYING_SPEED (MTH_FIXED (1.5))
SPRITE_INFO *flash = NULL;

void hurler_make(Fixed32 x, Fixed32 y) {
    SPRITE_INFO *hurler = sprite_next();
    sprite_make(hurler_chars[0], x, y, hurler);
    hurler->speed = HURLER_SPEED;
    hurler->animTimer = 0;
    hurler->iterate = &hurler_move;
}

void hurler_move(SPRITE_INFO *hurler) {
    if (hurler->animTimer++ > HURLER_ANIMTIME) {
        hurler->animTimer = 0;
        hurler->char_num = hurler_chars[hurler->animCursor];
        hurler->animCursor == 3 ? hurler->animCursor = 0 : hurler->animCursor++; //3 is size of hurler_chars array
    }
    hurler->state = 0;

    if ((hurler->xPos + (hurler->xSize >> 1) > player.xPos && hurler->xPos < (player.xPos + player.xSize)) || 
        (hurler->yPos + (hurler->ySize >> 1) > player.yPos && hurler->yPos < (player.yPos + player.ySize))) {
        hurler->speed = FLYING_SPEED;
    }
    else {
        hurler->speed = HURLER_SPEED;
    }

    if (hurler->xPos > player.xPos) {
        hurler->state |= SPRITE_LEFT;
    }
    else if (hurler->xPos < player.xPos) {
        hurler->state |= SPRITE_RIGHT;
    }
    if (hurler->yPos > player.yPos) {
        hurler->state |= SPRITE_UP;
    }
    else if (hurler->yPos < player.yPos) {
        hurler->state |= SPRITE_DOWN;
    }
    sprite_move(hurler, 0);


    // if (flash == NULL) {
    //     flash = sprite_next();
    //     sprite_make(61, hurler->xPos, hurler->yPos, flash);
    //     print_num(flash->index, 6, 0);
    // }
    // else {
    //     sprite_delete(flash);
    //     flash = NULL;
    // }
}