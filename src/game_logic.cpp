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
	gstate->base_velocity = 0.5;
	gstate->level_width = 0.0f;
	gstate->xpos = 0.0f;
	gstate->zpos = 0.0f;

	gstate->turn_rate = 30;
	gstate->turn_degrees_per_frame = (90.0f / gstate->turn_rate);
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
	float dist = (gstate->speed * gstate->base_velocity);
	switch (gstate->curr_dir) {
	case NORTH:
		gstate->zpos += dist;
		break;
	case SOUTH:
		gstate->zpos -= dist;
		break;
	case EAST:
		gstate->xpos += dist;
		break;
	case WEST:
		gstate->xpos -= dist;
		break;
	}
	if (gstate->zpos < 0)  gstate->zpos += 30;
	if (gstate->zpos > 30) gstate->zpos -= 30;
	if (gstate->xpos < 0)  gstate->xpos += 30;
	if (gstate->xpos > 30) gstate->xpos -= 30;
}
