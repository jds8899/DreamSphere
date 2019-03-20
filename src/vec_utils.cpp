
#include "vec_utils.h"
#include <kos/vector.h>
#include <plx/matrix.h>

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

void print_current_matr(char * label, bool pvr)
{
	matrix_t* m = (matrix_t*)malloc(sizeof(matrix_t));
	
	if (pvr) {
		//plx DEFINE pointint to pvr mat_store
		plx_mat_store(m);
	}
	else {
		//load parallax current matrix
		plx_mat3d_store(m);
	}

	printf(label);
	printf(":\n");

	//print matrix. matrix_t is just a typedef for float[4][4]-------
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%f ", m[i][j]);
		}
		printf("\n");
	}
	free(m);
}
