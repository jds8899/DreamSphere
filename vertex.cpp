#include "vertex.h"

Vertex::Vertex(vector_t vert, vector_t tx_coord, vector_t normal) :
	vert_(vert),
	tx_coord_(tx_coord),
	normal_(normal) {}

Vertex::Vertex() :
	vert_(),
	tx_coord_(),
	normal_() {}

Vertex::~Vertex()
{
}

vector_t Vertex::vert() {
	return vert_;
}

vector_t Vertex::tx_coord() {
	return tx_coord_;
}

vector_t Vertex::normal() {
	return normal_;
}
