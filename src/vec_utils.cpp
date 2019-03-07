
#include "vec_utils.h"

void vertex_submit(vector_t light, vector_t light_vert, vector_t vert, vector_t norm, vector_t tex, bool eos) {
	int flags = eos ? PVR_CMD_VERTEX_EOL : PVR_CMD_VERTEX;

	//printf("flag: %d, x:%f, y:%f, z:%f\n", flags, vert.x, vert.y, vert.z);
	plx_vert_fnp(flags, vert.x, vert.y, vert.z, 1, 1, 1, 1);
}

void vertex_submit_black(vector_t light, vector_t light_vert, vector_t vert, vector_t norm, vector_t tex, bool eos) {
	int flags = eos ? PVR_CMD_VERTEX_EOL : PVR_CMD_VERTEX;

	//printf("flag: %d, x:%f, y:%f, z:%f\n", flags, vert.x, vert.y, vert.z);
	plx_vert_fnp(flags, vert.x, vert.y, vert.z, .5, .5, .5, .5);
}