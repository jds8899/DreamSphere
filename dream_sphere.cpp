// DreamSphere.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <kos.h>

#include <plx/matrix.h>
#include <plx/prim.h>

#include "vertex.h"

KOS_INIT_FLAGS(INIT_DEFAULT);

bool done = false;

void init() {
	pvr_init_defaults();
	plx_mat3d_init();

	pvr_set_bg_color(1.0, 0.0, 0.0);
}

void update() {
	pvr_wait_ready();
	
	pvr_scene_begin();
	pvr_list_begin(PVR_LIST_OP_POLY);

	pvr_list_finish();
	pvr_scene_finish();
}

void cleanup() {
	pvr_shutdown();
}

int main(int argc, char *argv[]) {
	init();

	while (!done) {
		update();
	}

	cleanup();
}
