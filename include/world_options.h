#ifndef WORLD_OPTIONS_H
#define WORLD_OPTIONS_H

#include <kos.h>

typedef struct {
	unsigned size, tess;
} WorldOptions;

WorldOptions* world_options_init(unsigned size, unsigned tess);

void world_options_cleanup(WorldOptions* wo);

#endif
