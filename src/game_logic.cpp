#include "game_logic.h"

direction_t curr_dir = NORTH;
float speed = .1;
bool turning = false;
bool left = false;

void turn(int direction) {
	left = (direction == LEFT) ? true : false;
	curr_dir = (direction_t)((int)curr_dir + direction);
	if((int)curr_dir == -1) curr_dir = WEST;
	curr_dir = (direction_t)((int)curr_dir % (int)END);
	turning = true;
}
