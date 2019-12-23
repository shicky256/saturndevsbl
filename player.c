#include <sega_def.h>
#include <sega_mth.h>
#include <sega_scl.h>
#include "player.h"
#include "print.h"
#include "scroll.h"
#include "sprite.h"
#include "vblank.h"

#define PLAYER_ACCEL (MTH_FIXED(0.5))
#define PLAYER_MAXSPEED (MTH_FIXED(4))

extern Uint32 frame;
//maps to the D-Pad bitmap provided by the Saturn hardware
//what state the character should be set to given the d-pad's input
const Uint16 player_down[] = {37, 36, 38, 36}; //frames for when the player's walking down
const Uint16 player_up[] = {40, 39, 41, 39};
const Uint16 player_side[] = {43, 42, 44, 42};
int anim_cursor = 0;
SPRITE_INFO player;
//if you hold the fire button down, this keeps firing in the direction you were 
//moving initially (so you can fire and move in different directions)
Uint16 bullet_direction;
Uint32 bullet_lastframe = 0;
//how long after firing you have to wait before you can fire again
#define BULLET_DELAY (10) 

void player_init() {
	sprite_make(0, MTH_FIXED(48) + PLAYER_SPRITE_X, MTH_FIXED(16) + PLAYER_SPRITE_Y, &player);
}

void player_input() {
	Uint16 PadData1EW = PadData1E;
	PadData1E = 0;
	if (PadData1 & PAD_L) {
		if (player.dx > -PLAYER_MAXSPEED) {
			player.dx -= PLAYER_ACCEL;
		}
		else {
			player.dx = -PLAYER_MAXSPEED;
		}
		player.mirror = MIRROR_HORIZ;
	}
	else if (PadData1 & PAD_R) {
		if (player.dx < PLAYER_MAXSPEED) {
			player.dx += PLAYER_ACCEL;
		}
		else {
			player.dx = PLAYER_MAXSPEED;
		}
		player.mirror &= ~MIRROR_HORIZ;
	}
	else {
		if (player.dx > 0) {
			player.dx -= PLAYER_ACCEL;
		}
		else if (player.dx < 0) {
			player.dx += PLAYER_ACCEL;
		}		
	}
	player.xPos += player.dx;

	player_animate();
	// print_num(scrolls_x[0] >> 16, 0, 0); print_num(scrolls_x[0] & 0xffff, 0, 10);
	// print_num(scrolls_y[0] >> 16, 1, 0); print_num(scrolls_y[0] & 0xffff, 1, 10);
	// print_num(scrolls_x[1] >> 16, 2, 0); print_num(scrolls_x[1] & 0xffff, 2, 10);
	// print_num(scrolls_y[1] >> 16, 3, 0); print_num(scrolls_y[1] & 0xffff, 3, 10);
}

void player_animate() {
	
}
//allows me to treat the player sprite like any other sprite while only moving the screen
//around it
void player_draw() {
	sprite_draw(&player);
}
