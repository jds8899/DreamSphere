#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

enum direction{NORTH, SOUTH, EAST, WEST};

extern direction curr_dir;

const float base_velocity = .5;

// This is number of frames to turn 90 degrees
const float turn_rate = 100f;

extern float speed;

#endif
