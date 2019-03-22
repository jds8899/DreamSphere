#include "game_cxt.h"
#include "obj_model.h"
#include "obj_renderer.h"

// WORLD GLOBALS
WorldVA* world;
vector_t** wverts;
vector_t** wnorms;
vector_t** wtexs;
WorldOptions* wo;
unsigned stripn;
unsigned strips;

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

const unsigned WORLD_SIZE = 10;
const unsigned WORLD_TESS = 2;

pvr_poly_hdr_t nontextured_header;

pvr_poly_hdr_t textured_header;
pvr_ptr_t floor_tex;

void floor_tex_init() {
	floor_tex = pvr_mem_malloc(512 * 512 * 2);
	png_to_texture("/rd/checker1.png", floor_tex, PNG_NO_ALPHA);
}

void game_cxt_init() {
	floor_tex_init();

	// Setup Parallax Polygon Headers
	nontextured_header = create_nontextured_header();
	textured_header = create_textured_header(floor_tex, 512, 512);

	wo		= world_options_init(WORLD_SIZE, WORLD_TESS);
	world	= world_init(wo);

	vector_t** verts	= world->verts;
	vector_t** norms	= world->norms;
	vector_t** texs		= world->texs;

	unsigned vert_per_edge = world->vert_per_edge;

	stripn = vert_per_edge;
	strips = vert_per_edge * 2 + 2;

	wverts	= (vector_t**)malloc(stripn * sizeof(vector_t*));
	wnorms	= (vector_t**)malloc(stripn * sizeof(vector_t*));
	wtexs	= (vector_t**)malloc(stripn * sizeof(vector_t*));

	plx_mat_identity();
	plx_mat3d_apply_all();

	for (unsigned i = 0; i < stripn; ++i) {
		vector_t* trans_verts = (vector_t*)malloc(strips * sizeof(vector_t));

		plx_mat_transform(verts[i], trans_verts, strips, 4 * sizeof(float));

		//printf("x:%f, y:%f, z:%f\n", verts[i][0].x, verts[i][0].y, verts[i][0].z);
		//printf("x:%f, y:%f, z:%f\n", trans_verts[0].x, trans_verts[0].y, trans_verts[0].z);
		wverts[i] = trans_verts;

		wnorms[i] = (vector_t*)malloc(strips * sizeof(vector_t));
		wtexs[i]  = (vector_t*)malloc(strips * sizeof(vector_t));

		for (unsigned j = 0; j < strips; ++j) {
			wnorms[i][j] = norms[i][j];
			wtexs[i][j]  = texs[i][j];
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

void game_cxt_render() {
	pvr_list_begin(PVR_LIST_OP_POLY);
	pvr_prim(&textured_header, sizeof(pvr_poly_hdr_t));

	vector_t n = {0,0,0,0};

	for(unsigned i = 0; i < stripn; ++i) {
		for(unsigned j = 0; j < strips - 1; ++j) {
			vertex_submit(n, n, wverts[i][j], n, wtexs[i][j]);
		}
		vertex_submit(n, n, wverts[i][strips - 1], n, wtexs[i][strips - 1], true);
	}

	obj_render(cube, &nontextured_header);

	pvr_list_finish();

	for(unsigned i = 0; i < stripn; ++i) {
		for(unsigned j = 0; j < strips - 1; ++j) {
			wtexs[i][j].y = fmod((wtexs[i][j].y - (speed * base_velocity)), (float)WORLD_SIZE);
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
