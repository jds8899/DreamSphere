// DreamSphere.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <kos.h>

#include <plx/matrix.h>
#include <plx/prim.h>

#include "vertex.h"
#include "world_va.h"
#include "world_options.h"

#define DEBUG_GAME

KOS_INIT_FLAGS(INIT_DEFAULT);

enum game_cxt {MENU, GAME, PAUSE};

// GAME STATE GLOBALS
bool done = false;
pvr_poly_hdr_t nontextured_header;
game_cxt gcxt = MENU;

// WORLD GLOBALS
vector_t** wverts;
vector_t** wnorms;
vector_t** wtexs;
WorldOptions wo(10, 2);
unsigned stripn;
unsigned strips;

void vertex_submit(vector_t light, vector_t light_vert, vector_t vert, vector_t norm, vector_t tex, bool eos = false) {
	int flags = eos ? PVR_CMD_VERTEX_EOL : PVR_CMD_VERTEX;

	//printf("flag: %d, x:%f, y:%f, z:%f\n", flags, vert.x, vert.y, vert.z);
	plx_vert_fnp(flags, vert.x, vert.y, vert.z, 1, 1, 1, 1);
}

void menu_cxt_init() {

}

void game_cxt_init() {
	WorldVA world(wo);

	vector_t** verts	= world.verts();
	//vector_t** norms	= world.norms();
	//vector_t** texs		= world.texs();

	stripn = world.strip_num();
	strips = world.strip_size();

	wverts	= (vector_t**)malloc(stripn * sizeof(vector_t*));
	//wnorms	= (vector_t**)malloc(stripn * sizeof(vector_t*));
	//wtexs	= (vector_t**)malloc(stripn * sizeof(vector_t*));

	plx_mat_identity();
	plx_mat3d_apply_all();

	for (unsigned i = 0; i < stripn; ++i) {
		vector_t* trans_verts = (vector_t*)malloc(strips * sizeof(vector_t));

		plx_mat_transform(verts[i], trans_verts, strips, 4 * sizeof(float));

		printf("x:%f, y:%f, z:%f\n", verts[i][0].x, verts[i][0].y, verts[i][0].z);
		printf("x:%f, y:%f, z:%f\n", trans_verts[0].x, trans_verts[0].y, trans_verts[0].z);
		wverts[i] = trans_verts;
		/*
		norms[i] = (vector_t*)malloc(strips * sizeof(vector_t));
		texs[i]  = (vector_t*)malloc(strips * sizeof(vector_t));
		
		for (unsigned j = 0; j < strips; ++j) {
			wnorms[i][j] = norms[i][j];
			wtexs[i][j]  = texs[i][j];
		}
		*/
	}
}

void pause_cxt_init() {

}

void menu_cxt_prep() {

}

void game_cxt_prep() {
	//plx_mat_identity();
	//plx_mat3d_apply_all();
}

void pause_cxt_prep() {

}

void menu_cxt_render() {
	pvr_list_begin(PVR_LIST_OP_POLY);

	pvr_list_finish();
}

void game_cxt_render() {
	pvr_list_begin(PVR_LIST_OP_POLY);
	pvr_prim(&nontextured_header, sizeof(pvr_poly_hdr_t));

	vector_t n = {0,0,0,0};

	for(unsigned i = 0; i < stripn; ++i) {
		for(unsigned j = 0; j < strips - 1; ++j) {
			vertex_submit(n, n, wverts[i][j], n, n);
		}
		vertex_submit(n, n, wverts[i][strips - 1], n, n, true);
	}

	pvr_list_finish();
}

void pause_cxt_render() {
	pvr_list_begin(PVR_LIST_OP_POLY);

	pvr_list_finish();
}

void menu_cxt_cleanup() {

}

void game_cxt_cleanup() {
}

void pause_cxt_cleanup() {

}

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
	init();

	while (!done) {
		update();
	}

	cleanup();
}
