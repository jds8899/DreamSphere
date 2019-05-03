#include "game_logic.h"

GameState* gstate = 0;

void game_state_init()
{
	gstate = (GameState*) malloc(sizeof(GameState));

	gstate->curr_dir = NORTH;
	gstate->sonic_direction = { 0.0, 0.0, 1.0, 0.0 }; //Initially "north", along +z axis
	gstate->sonic_turn_degrees = 0;
	gstate->speed = .1;
	gstate->turning = false;
	gstate->left = false;
	gstate->jumping = false;
	gstate->xpos = 0.0f;
	gstate->zpos = 0.0f;

	gstate->turn_rate = 30;
	gstate->turn_degrees_per_frame = (90.0f / gstate->turn_rate);

	gstate->level_width = 0.0f;
	gstate->display_plane_width = 0.0f;
	gstate->level_to_world_space = 0.0f;
}

void game_state_cleanup()
{
	free(gstate);
}

void turn(int direction) {
	gstate->left = (direction == LEFT) ? true : false;
	gstate->curr_dir = (direction_t)((int)gstate->curr_dir + direction);
	if((int)gstate->curr_dir == -1) gstate->curr_dir = WEST;
	gstate->curr_dir = (direction_t)((int)gstate->curr_dir % (int)END);
	gstate->turning = true;
}

void update_pos() {

	switch (gstate->curr_dir) {
	case NORTH:
		gstate->zpos += gstate->speed;
		break;
	case SOUTH:
		gstate->zpos -= gstate->speed;
		break;
	case EAST:
		gstate->xpos += gstate->speed;
		break;
	case WEST:
		gstate->xpos -= gstate->speed;
		break;
	}

	if (gstate->zpos < 0)  gstate->zpos += gstate->level_width;
	if (gstate->zpos > gstate->level_width) gstate->zpos -= gstate->level_width;
	if (gstate->xpos < 0)  gstate->xpos += gstate->level_width;
	if (gstate->xpos > gstate->level_width) gstate->xpos -= gstate->level_width;
}
