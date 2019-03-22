#include <kos.h>

#include <plx/matrix.h>
#include <plx/prim.h>

#include "vertex.h"
#include "game_cxt.h"
#include "menu_cxt.h"
#include "pause_cxt.h"
#include "obj_model.h"
#include "action.h"
#include "utils.h"

#define DEBUG_GAME

//#define DEBUG_CONTROLS

KOS_INIT_FLAGS(INIT_DEFAULT);

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

enum game_cxt {MENU, GAME, PAUSE};

// GAME STATE GLOBALS
bool done = false;
game_cxt gcxt = MENU;

void init() {
	// Initialize gfx libs
	pvr_init_defaults();
	plx_mat3d_init();


	pvr_set_bg_color(0.0, 0.0, 0.0);

	// Camera
	plx_mat3d_mode(PLX_MAT_PROJECTION);
	plx_mat3d_identity();
	plx_mat3d_perspective(60.0f, 640.0f / 480.0f, .1f, 100.0f); // FOV, Aspect Ratio, znear, zfar

	plx_mat3d_mode(PLX_MAT_MODELVIEW);
	plx_mat3d_identity();

	point_t  camera_pos	= {0.0f, 1.0f, 5.0f, 1.0f};
	point_t  lookat		= {0.0f, 0.0f, 0.0f, 1.0f};
	vector_t up			= {0.0f, 1.0f, 0.0f, 0.0f};

	//test diagonal view downward of plane/cube
	/*point_t  camera_pos = { 0.0f, 5.0f, 5.0f, 1.0f };
	point_t  lookat = { 0.0f, 0.0f, 0.0f, 1.0f };
	vector_t up = { 0.0f, 1.0f, -1.0f, 0.0f };*/

	//test cam pos from above
	/*point_t  camera_pos = { 0.0f, 20.0f, 0.0f, 1.0f };
	point_t  lookat = { 0.0f, 0.0f, 0.0f, 1.0f };
	vector_t up = { 0.0f, 0.0f, -1.0f, 0.0f };*/
	plx_mat3d_lookat(&camera_pos, &lookat, &up);

#ifdef DEBUG_GAME
	game_cxt_init();
#endif

}

#ifdef DEBUG_GAME
void update() {
	game_cxt_prep();

	pvr_wait_ready();
	
	pvr_scene_begin();

	game_cxt_render();

	pvr_scene_finish();
}
#else
void update() {
	switch(gcxt) {
	case MENU:
		menu_cxt_prep();
		break;
	case GAME:
		game_cxt_prep();
		break;
	case PAUSE:
		pause_cxt_prep();
		break;
	}

	pvr_wait_ready();
	
	pvr_scene_begin();

	switch(gcxt) {
	case MENU:
		menu_cxt_render();
		break;
	case GAME:
		game_cxt_render();
		break;
	case PAUSE:
		pause_cxt_render();
		break;
	}

	pvr_scene_finish();
}
#endif

void cleanup() {
	pvr_shutdown();

#ifdef DEBUG_GAME
	game_cxt_cleanup();
#endif
}

int main(int argc, char *argv[]) {

	//ObjModel* obj = obj_get("/rd/cube.obj");

	//if (obj == 0) return 1;
	//print_tiny_attrib(obj->attrib);
	//obj_cleanup(obj);
	//obj = 0;

	//for (;;) {}

#ifdef DEBUG_CONTROLS
	bool exitProgram = false;

	while (!exitProgram)
	{
		maple_device_t *controller = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);
		cont_state_t *controllerState = (cont_state_t*)maple_dev_status(controller);
		if (controllerState->buttons & CONT_START)
			exitProgram = true;

		SonicAction_t act1 = get_action(controllerState);

		switch (act1) {
		case ACT_MOVEFORWARD:
			printf("ACT_MOVEFORWARD\n");
			break;
		case ACT_TURNLEFT:
			printf("ACT_TURNLEFT\n");
			break;
		case ACT_TURNRIGHT:
			printf("ACT_TURNRIGHT\n");
			break;
		case ACT_JUMP:
			printf("ACT_JUMP\n");
			break;
		case ACT_NONE:
			//printf("ACT_INVALID\n");
			break;
		default:
			//printf("unknown");
			break;
		}
	}
#endif //End DEBUG_CONTROLS

	init();

	while (!done) {
		update();
	}

	cleanup();
}
