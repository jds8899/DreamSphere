#include "game_cxt.h"

// WORLD GLOBALS
WorldVA* world;
vector_t** wverts;
vector_t** wnorms;
vector_t** wtexs;
WorldOptions* wo;
unsigned stripn;
unsigned strips;

void game_cxt_init() {
	wo		= world_options_init(10, 2);
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
		/*
		for (unsigned j = 0; j < strips; ++j) {
			wnorms[i][j] = norms[i][j];
			wtexs[i][j]  = texs[i][j];
		}
		*/
	}
}

void game_cxt_prep() {
	//plx_mat_identity();
	//plx_mat3d_apply_all();
}

void game_cxt_render(pvr_poly_hdr_t* hdr) {
	pvr_list_begin(PVR_LIST_OP_POLY);
	pvr_prim(hdr, sizeof(pvr_poly_hdr_t));

	vector_t n = {0,0,0,0};

	for(unsigned i = 0; i < stripn; ++i) {
		for(unsigned j = 0; j < strips - 1; ++j) {
			vertex_submit(n, n, wverts[i][j], n, n);
		}
		vertex_submit(n, n, wverts[i][strips - 1], n, n, true);
	}

	pvr_list_finish();
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
}
