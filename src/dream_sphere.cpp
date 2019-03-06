#include <kos.h>

#include <plx/matrix.h>
#include <plx/prim.h>

#include "vertex.h"
#include "game_cxt.h"
#include "menu_cxt.h"
#include "pause_cxt.h"
#include "obj_model.h"

#define DEBUG_GAME

KOS_INIT_FLAGS(INIT_DEFAULT);

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

enum game_cxt {MENU, GAME, PAUSE};

// GAME STATE GLOBALS
bool done = false;
pvr_poly_hdr_t nontextured_header;
game_cxt gcxt = MENU;

void init() {
	// Initialize gfx libs
	pvr_init_defaults();
	plx_mat3d_init();

	// Setup Parallax Polygon Header
	pvr_poly_cxt_t nontextured_context;
	pvr_poly_cxt_col(&nontextured_context, PVR_LIST_OP_POLY);
	nontextured_context.gen.culling = PVR_CULLING_NONE;
	pvr_poly_compile(&nontextured_header, &nontextured_context);

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

	game_cxt_render(&nontextured_header);

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
		game_cxt_render(&nontextured_header);
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

	ObjModel* obj = obj_get("/rd/cube.obj");

	if (obj == 0) return 1;
	print_tiny_attrib(obj->attrib);
	obj_cleanup(obj);
	obj = 0;

	init();

	while (!done) {
		update();
	}

	cleanup();
}
