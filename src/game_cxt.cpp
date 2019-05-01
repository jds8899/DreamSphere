#include "game_cxt.h"
#include "obj_model.h"
#include "obj_renderer.h"
#include "level_data.h"

// WORLD GLOBALS
WorldVA* world;
vector_t** wverts;
vector_t** wnorms;
vector_t** wtexs;
WorldOptions* wo;
unsigned stripn;
unsigned strips;

vector_t** trans;

// OBJ model information

// Model indices in loaded OBJ array
//#define CUBE_MODEL 0
//#define SPHERE_MODEL 1

// Loaded OBJ models. Can be reused to display multiple objects, perhaps?
//ObjModel** loadedModels;

// Locations of spheres
//vector_t** sphereLocations;

ObjModel* cube;
vector_t cubePos;

float deg;

LevelData_t* lebel;
vector_t**	 obj_ofsts;

pvr_poly_hdr_t nontextured_header;
pvr_poly_hdr_t object_header;

pvr_poly_hdr_t textured_header;
pvr_ptr_t floor_tex;

void floor_tex_init() {
	floor_tex = pvr_mem_malloc(512 * 512 * 2);
	png_to_texture("/rd/checker1.png", floor_tex, PNG_NO_ALPHA);
}

void game_cxt_init() {
	floor_tex_init();

	// Setup Parallax Polygon Headers
	nontextured_header = create_nontextured_header(true);

	object_header = create_nontextured_header(false);

	textured_header = create_textured_header(floor_tex, 512, 512);

	deg = (90.0f / turn_rate);

#ifdef DEBUG_GAME

	lebel   = read_level("/rd/test_level");
	obj_dim = lebel->obj_dim;
	xpos    = obj_dim / 2;
	zpos    = obj_dim / 2;

#endif

	world	= world_init(lebel->wo);

	vector_t** verts	= world->verts;
	vector_t** norms	= world->norms;
	vector_t** texs		= world->texs;

	unsigned vert_per_edge = world->vert_per_edge;

	stripn = vert_per_edge;
	strips = vert_per_edge * 2 + 2;

	wverts	= (vector_t**)malloc(stripn * sizeof(vector_t*));
	trans	= (vector_t**)malloc(stripn * sizeof(vector_t*));
	wnorms	= (vector_t**)malloc(stripn * sizeof(vector_t*));
	wtexs	= (vector_t**)malloc(stripn * sizeof(vector_t*));

	plx_mat_identity();
	plx_mat3d_apply_all();

	for (unsigned i = 0; i < stripn; ++i) {
		//vector_t* trans_verts = (vector_t*)malloc(strips * sizeof(vector_t));
		wverts[i] = (vector_t*)malloc(strips * sizeof(vector_t));
		trans[i] = (vector_t*)malloc(strips * sizeof(vector_t));

		//plx_mat_transform(verts[i], trans_verts, strips, 4 * sizeof(float));

		//printf("x:%f, y:%f, z:%f\n", verts[i][0].x, verts[i][0].y, verts[i][0].z);
		//printf("x:%f, y:%f, z:%f\n", trans_verts[0].x, trans_verts[0].y, trans_verts[0].z);
		//wverts[i] = trans_verts;

		wnorms[i] = (vector_t*)malloc(strips * sizeof(vector_t));
		wtexs[i]  = (vector_t*)malloc(strips * sizeof(vector_t));

		for (unsigned j = 0; j < strips; ++j) {
			wnorms[i][j] = norms[i][j];
			wtexs[i][j]  = texs[i][j];
			wverts[i][j] = verts[i][j];
			//printf("u:%f, v:%f\n", wtexs[i][j].x, wtexs[i][j].y);
		}
	}

	//globals
	cube = obj_get("/rd/cube.obj");
	cubePos = { 0,0,0,1 };
}

void game_cxt_prep() {
	//plx_mat_identity();
	//plx_mat3d_apply_all();
}

int curr_turn = 0;

void game_cxt_render() {
	pvr_list_begin(PVR_LIST_OP_POLY);
	pvr_prim(&textured_header, sizeof(pvr_poly_hdr_t));

	vector_t n = {0,0,0,0};

	//TODO: May want to consolidate some of these loops
	if (turning) {
		if (left) curr_turn += deg;
		else	 curr_turn -= deg;
	}
	plx_mat3d_push();
	plx_mat_identity();
	plx_mat3d_rotate((float)curr_turn, 0.0f, 1.0f, 0.0f);
	plx_mat_identity();
	plx_mat3d_apply_all();
	
	for (unsigned i = 0; i < stripn; ++i) {
		plx_mat_transform(wverts[i], trans[i], strips, 4 * sizeof(float));
	}

	plx_mat3d_pop();

	if (curr_turn % 90 == 0 && turning) {
		turning = false;
	}


	for(unsigned i = 0; i < stripn; ++i) {
		for(unsigned j = 0; j < strips - 1; ++j) {
			vertex_submit(n, n, trans[i][j], n, wtexs[i][j]);
		}
		vertex_submit(n, n, trans[i][strips - 1], n, wtexs[i][strips - 1], true);
	}

	obj_render(cube, &object_header);

	pvr_list_finish();

	if (!turning) {
		update_pos();
		for (unsigned i = 0; i < stripn; ++i) {
			for (unsigned j = 0; j < strips - 1; ++j) {
				switch (curr_dir) {
				case NORTH:
					wtexs[i][j].y = fmod((wtexs[i][j].y - (speed * base_velocity)), (float)lebel->wo->size);
					break;
				case SOUTH:
					wtexs[i][j].y = fmod((wtexs[i][j].y + (speed * base_velocity)), (float)lebel->wo->size);
					break;
				case EAST:
					wtexs[i][j].x = fmod((wtexs[i][j].x - (speed * base_velocity)), (float)lebel->wo->size);
					break;
				case WEST:
					wtexs[i][j].x = fmod((wtexs[i][j].x + (speed * base_velocity)), (float)lebel->wo->size);
					break;
				}
			}
		}
	}
}

void game_cxt_cleanup() {
	world_options_cleanup(wo);
	world_cleanup(world);

	for (unsigned i = 0; i < stripn; ++i) {
		free(wverts[i]);
		free(wnorms[i]);
		free(wtexs[i]);
	}
	free(wverts);
	free(wnorms);
	free(wtexs);

	obj_cleanup(cube);
}
