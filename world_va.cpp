#include "world_va.h"

void build_world_(WorldVA* wva);


WorldVA* world_init(WorldOptions* wo) {
	WorldVA* ret = (WorldVA*)malloc(sizeof(WorldVA));

	unsigned size			= wo->size;
	unsigned tess			= wo->tess;
	unsigned vert_per_edge	= size * tess;
	ret->size				= size;
	ret->tess				= tess;
	ret->vert_per_edge		= vert_per_edge;
	ret->vert_count			= vert_per_edge * vert_per_edge;
	ret->verts				= (vector_t**)malloc((vert_per_edge) * sizeof(vector_t*));
	ret->norms				= (vector_t**)malloc((vert_per_edge) * sizeof(vector_t*));
	ret->texs				= (vector_t**)malloc((vert_per_edge) * sizeof(vector_t*));

	for (unsigned i = 0; i < vert_per_edge; ++i) {
		ret->verts[i] = (vector_t*)malloc((vert_per_edge * 2 + 2) * sizeof(vector_t));
		ret->norms[i] = (vector_t*)malloc((vert_per_edge * 2 + 2) * sizeof(vector_t));
		ret->texs[i]  = (vector_t*)malloc((vert_per_edge * 2 + 2) * sizeof(vector_t));
	}

	build_world_(ret);
	return ret;
}


void world_cleanup(WorldVA* wva) {
	for (unsigned i = 0; i < wva->vert_per_edge; ++i) {
		free(wva->verts[i]);
		free(wva->norms[i]);
		free(wva->texs[i]);
	}
	free(wva->verts);
	free(wva->norms);
	free(wva->texs);
	free(wva);
	wva = NULL;
}

void build_world_(WorldVA* wva) {
	unsigned tess			= wva->tess;
	unsigned size			= wva->size;
	unsigned vert_per_edge	= wva->vert_per_edge;
	float    step			= 1.0f / tess;

	for (unsigned i = 0; i < vert_per_edge; ++i) {
		//printf("STRIP %x/%x\n", i + 1, vert_per_edge_);
		for (unsigned j = 0; j < vert_per_edge + 1; ++j) {

			float x0	=  i * step - size / 2.0f;
			float x1	= (i + 1) * step - size / 2.0f;
			float y		=  0.0f;
			float z		=  j * step - size / 2.0f;

			float u0	= (i * step) / 2.0f;
			float u1	= (i + 1) * step / 2.0f;
			float v		= (j * step) / 2.0f;

			vector_t p0 = {x0, y, z, 1.0f};
			vector_t p1 = {x1, y, z, 1.0f};

			//printf("verts_[%x][%x]: %f, %f, %f\n", i, j * 2, p0.x, p0.y, p0.z);
			//printf("verts_[%x][%x]: %f, %f, %f\n", i, (j * 2) + 1, p1.x, p1.y, p1.z);

			vector_t n = {0.0f, 1.0f, 0.0f, 0.0f};

			vector_t t0 = {u0, v, 0.0f, 1.0f};
			vector_t t1 = {u1, v, 0.0f, 1.0f};

			wva->verts[i][j * 2]		= p0;
			wva->verts[i][j * 2 + 1]	= p1;

			wva->norms[i][j * 2]		= n;
			wva->norms[i][j * 2 + 1]	= n;

			wva->texs[i][j * 2]			= t0;
			wva->texs[i][j * 2 + 1]		= t1;
		}
	}
}
