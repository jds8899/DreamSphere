#ifndef WORLD_VA_H
#define WORLD_VA_H

#include "world_options.h"
#include <kos.h>

typedef struct {
	vector_t** verts;
	vector_t** norms;
	vector_t** texs; // texs for naming consistency ;)))))))))
	unsigned size, tess, vert_per_edge, vert_count;
} WorldVA;

WorldVA* world_init(WorldOptions* wo);

void world_cleanup(WorldVA* wva);

#endif