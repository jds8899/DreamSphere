/*
Functions for determining what action sonic is performing.
*/

#ifndef ACTION_H
#define ACTION_H

#include <kos.h>

/*
Enum for possible actions Sonic can do.
*/
typedef enum{
	ACT_MOVEFORWARD,
	ACT_TURNLEFT,
	ACT_TURNRIGHT,
	ACT_JUMP,
	ACT_NONE
} SonicAction_t;

/*
Get next action to perform, given a controller state.

@param controllerState Pointer to state of main controller.

@return Enum of next action Sonic should take when able
*/
SonicAction_t get_action(cont_state_t *controllerState);


#endif