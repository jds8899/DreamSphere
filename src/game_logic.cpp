#include "game_logic.h"

direction_t curr_dir = NORTH;
vector_t sonic_direction = { 0.0, 0.0, 1.0, 0.0 }; //Initially "north", along +z axis
float speed   = .1;
bool turning  = false;
bool left     = false;
bool jumping = false;
float obj_dim = 0.0f;
float xpos    = 0.0f;
float zpos    = 0.0f;

void turn(int direction) {
	left = (direction == LEFT) ? true : false;
	curr_dir = (direction_t)((int)curr_dir + direction);
	if((int)curr_dir == -1) curr_dir = WEST;
	curr_dir = (direction_t)((int)curr_dir % (int)END);
	turning = true;
}

void update_pos() {
	float dist = (speed * base_velocity);
	switch (curr_dir) {
	case NORTH:
		zpos += dist;
		break;
	case SOUTH:
		zpos -= dist;
		break;
	case EAST:
		xpos += dist;
		break;
	case WEST:
		xpos -= dist;
		break;
	}
	if (zpos < 0)  zpos += 30;
	if (zpos > 30) zpos -= 30;
	if (xpos < 0)  xpos += 30;
	if (xpos > 30) xpos -= 30;
}
