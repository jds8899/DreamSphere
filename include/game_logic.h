#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <kos.h>
#include <kos/vector.h>

#define LEFT  -1
#define RIGHT  1

enum direction_t{NORTH, EAST, SOUTH, WEST, END};

typedef struct{

	//Sonic's current direction along the level grid
	direction_t curr_dir;

	//Sonic's current direction in the world (even while turning).
	//Used for rendering objects
	vector_t sonic_direction;

	//Temporary variable to aid with refactoring turning.
	//This is sonic's current degrees turned from his starting direction.
	int sonic_turn_degrees;

	//Sonic's speed
	float speed;

	//Level grid length
	float level_width;

	//Sonic's position
	float xpos, zpos;

	//If sonic is currently turning
	bool turning;

	//If sonic is currently turning LEFT. Otherwise right
	bool left;

	//If sonic is currently midair
	bool jumping;

	//?
	float base_velocity;

	// This is number of frames to turn 90 degrees
	float turn_rate;

	//Number of degrees sonic turns per frame
	float turn_degrees_per_frame;
} GameState;

extern GameState* gstate;

/*
Initialize singleton game state struct.
Currently, values are all hard coded in this function.
Can be changed later.
*/
void game_state_init();

/*
Clean up game state resources.
*/
void game_state_cleanup();

/*
Turn sonic to face a certain direction.

@param direction -1 or 1 to indicate left/right
*/
void turn(int direction);

/*
Update sonic's position based on his current speed and orientation
*/
void update_pos();

#endif
