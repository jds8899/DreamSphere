#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <kos.h>

#define LEFT  -1
#define RIGHT  1

enum direction_t{NORTH, EAST, SOUTH, WEST, END};

extern direction_t curr_dir;

extern float speed;

extern float obj_dim;

extern float xpos, zpos;

extern bool turning;

extern bool left;

const float base_velocity = .5;

// This is number of frames to turn 90 degrees
const float turn_rate = 30;

void turn(int direction);

void update_pos();

#endif
