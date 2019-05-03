#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <kos.h>
#include <kos/vector.h>

#define LEFT  -1
#define RIGHT  1

enum direction_t{NORTH, EAST, SOUTH, WEST, END};

//Sonic's current direction along the level grid
extern direction_t curr_dir;

//Sonic's current direction in the world (even while turning).
//Used for rendering objects
extern vector_t sonic_direction;

//Sonic's speed
extern float speed;

//Level grid length
extern float obj_dim;

//Sonic's position
extern float xpos, zpos;

//If sonic is currently turning
extern bool turning;

//If sonic is currently turning LEFT. Otherwise right
extern bool left;

//If sonic is currently midair
extern bool jumping;

//?
const float base_velocity = .5;

// This is number of frames to turn 90 degrees
const float turn_rate = 30;

void turn(int direction);

void update_pos();

#endif
