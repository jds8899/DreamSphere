#ifndef VERTEX_H
#define VERTEX_H

#include <kos.h>

class Vertex
{
public:
	Vertex(vector_t vert, vector_t tx_coord, vector_t normal);
	Vertex();
	~Vertex();
	vector_t vert();
	vector_t tx_coord();
	vector_t normal();
private:
	vector_t vert_, tx_coord_, normal_;
};

#endif
