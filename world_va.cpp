#include "world_va.h"


WorldVA::WorldVA(WorldOptions wo) :
	verts_(),
	norms_(),
	texs_(),
	size_(),
	tess_(),
	vert_per_edge_(),
	vert_count_() {
		size_			= wo.size();
		tess_			= wo.tess();
		vert_per_edge_	= size_ * tess_;
		vert_count_		= vert_per_edge_ * vert_per_edge_;
		verts_			= (vector_t**)malloc((vert_per_edge_) * sizeof(vector_t*));
		norms_			= (vector_t**)malloc((vert_per_edge_) * sizeof(vector_t*));
		texs_			= (vector_t**)malloc((vert_per_edge_) * sizeof(vector_t*));

		for (unsigned i = 0; i < vert_per_edge_; ++i) {
			verts_[i] = (vector_t*)malloc((vert_per_edge_ * 2 + 2) * sizeof(vector_t));
			norms_[i] = (vector_t*)malloc((vert_per_edge_ * 2 + 2) * sizeof(vector_t));
			texs_[i]  = (vector_t*)malloc((vert_per_edge_ * 2 + 2) * sizeof(vector_t));
		}

		build_world_();
}


WorldVA::~WorldVA() {
	for (unsigned i = 0; i < vert_per_edge_; ++i) {
		free(verts_[i]);
		free(norms_[i]);
		free(texs_[i]);
	}
	free(verts_);
	free(norms_);
	free(texs_);
}

unsigned WorldVA::strip_num() {
	return vert_per_edge_;
}

unsigned WorldVA::strip_size() {
	return vert_per_edge_ * 2 + 2;
}

vector_t** WorldVA::verts() {
	return verts_;
}

vector_t** WorldVA::norms() {
	return norms_;
}

vector_t** WorldVA::texs() {
	return texs_;
}

void WorldVA::build_world_() {
	float step = 1.0f / tess_;
	for (unsigned i = 0; i < vert_per_edge_; ++i) {
		//printf("STRIP %x/%x\n", i + 1, vert_per_edge_);
		for (unsigned j = 0; j < vert_per_edge_ + 1; ++j) {

			float x0	=  i * step - size_ / 2.0f;
			float x1	= (i + 1) * step - size_ / 2.0f;
			float y		=  0.0f;
			float z		=  j * step - size_ / 2.0f;

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

			verts_[i][j * 2]		= p0;
			verts_[i][j * 2 + 1]	= p1;

			norms_[i][j * 2]		= n;
			norms_[i][j * 2 + 1]	= n;

			texs_[i][j * 2]			= t0;
			texs_[i][j * 2 + 1]		= t1;
		}
	}
}
