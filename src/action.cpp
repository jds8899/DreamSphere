/*
Functions for determining what action sonic is performing.
*/

#include <kos.h>
#include "action.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

SonicAction_t get_action(cont_state_t *controllerState) {
	int btns = controllerState->buttons;

	//Jump should have highest priority
	if (btns & CONT_A || btns & CONT_B || btns & CONT_X || btns & CONT_Y)
		return ACT_JUMP;

	//true if x-axis joystick position more extreme than y-axis position
	bool xGreater = abs(controllerState->joyx) > abs(controllerState->joyy);

	// turn if dpad left/right or joystick x is highly left/right
	if (btns & CONT_DPAD_LEFT || (xGreater && controllerState->joyx < 0))
		return ACT_TURNLEFT;

	if (btns & CONT_DPAD_RIGHT || (xGreater && controllerState->joyx > 0))
		return ACT_TURNRIGHT;

	//forward if dpad up or y axis strongly negative (held up)
	if (btns & CONT_DPAD_UP || ((!xGreater) && controllerState->joyy < 0))
		return ACT_MOVEFORWARD;
	
	return ACT_NONE;
}
