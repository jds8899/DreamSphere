#include "world_options.h"

WorldOptions* world_options_init(unsigned size, unsigned tess) {
	WorldOptions* ret	= (WorldOptions*)malloc(sizeof(WorldOptions));
	ret->size			= size;
	ret->tess			= tess;

	return ret;
}

void world_options_cleanup(WorldOptions* wo) {
	free(wo);
}
