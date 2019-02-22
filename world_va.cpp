#include "pch.h"
#include "world_va.h"


WorldVA::WorldVA(WorldOptions wo) :
	wva_(),
	size_(),
	tess_(),
	vert_per_edge_(),
	vert_count_() {
		size_			= wo.size();
		tess_			= wo.tess();
		vert_per_edge_	= size_ * tess_;
		vert_count_		= vert_per_edge_ * vert_per_edge_;
		wva_			= new Vertex*[vert_per_edge_ - 1];

		for (unsigned i = 0; i < vert_per_edge_ - 1; ++i) {
			wva_[i] = new Vertex[vert_per_edge_ * 2];
		}

		build_world_();
}


WorldVA::~WorldVA() {
	for (unsigned i = 0; i < vert_per_edge_ - 1; ++i) {
		delete[] wva_[i];
	}
	delete[] wva_;
}

Vertex** WorldVA::wva() {
	return wva_;
}

void WorldVA::build_world_() {
	float step = 1.0f / tess_;
	for (unsigned i = 0; i < vert_per_edge_ - 1; ++i) {
		for (unsigned j = 0; j < vert_per_edge_; ++j) {

			float x0	=  i * step - size_ / 2.0f;
			float x1	= (i + 1) * step - size_ / 2.0f;
			float y		=  0.0f;
			float z		=  j * step - size_ / 2.0f;

			float u0	= (i * step) / 2.0f;
			float u1	= (i + 1) * step / 2.0f;
			float v		= (j * step) / 2.0f;

			vector_t p0 = {x0, y, z, 0.0f};
			vector_t p1 = {x1, y, z, 0.0f};

			vector_t n = {0.0f, 1.0f, 0.0f, 1.0f};

			vector_t t0 = {u0, v, 0.0f, 0.0f};
			vector_t t1 = {u1, v, 0.0f, 0.0f};

			Vertex v0(p0, t0, n);
			Vertex v1(p1, t1, n);

			wva_[i][j * 2]		= v0;
			wva_[i][j * 2 + 1]	= v1;
		}
	}
}
