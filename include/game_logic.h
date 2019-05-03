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

//Temporary variable to aid with refactoring turning.
//This is sonic's current degrees turned from his starting direction.
extern int sonic_turn_degrees;

//Sonic's speed
extern float speed;

//Level grid length
extern float level_width;

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
extern float turn_rate;

//Number of degrees sonic turns per frame
extern float turn_degrees_per_frame;

void turn(int direction);

void update_pos();

#endif
