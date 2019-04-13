#include "level_data.h"

LevelData_t* read_level(const char* path) {
	LevelData_t* ret = (LevelData_t*)malloc(sizeof(LevelData_t));
	ret->wo = (WorldOptions*)malloc(sizeof(WorldOptions));

	FILE* f = fopen(path, "rb"); // was "rb"
	int size, tess;
	unsigned int obj_dim;
	fscanf(f, "%d", &size);
	fscanf(f, "%d", &tess);
	fscanf(f, "%u", &obj_dim);
	ret->wo->size = size;
	ret->wo->tess = tess;
	ret->obj_dim = obj_dim;

	ret->layout = (ObjectType_t**)malloc(sizeof(ObjectType_t*) * obj_dim);

	char read;
	ObjectType_t obj;

	fscanf(f, "%c", &read); // Read newline and carriage return
	fscanf(f, "%c", &read); // Get rid of one of these if not using windows line ends

	for (int i = 0; i < obj_dim; ++i) {
		ret->layout[i] = (ObjectType_t*)malloc(sizeof(ObjectType_t) * obj_dim);
		for (int j = 0; j < obj_dim; ++j) {
			fscanf(f, "%c", &read);
			switch (read) {
			case 'B':  // Blue
				obj = BLUE;
				break;
			case 'R':  // Red
				obj = RED;
				break;
			case 'b':  // bumper
				obj = BUMP;
				break;
			case 'r':  // ring
				obj = RING;
				break;
			case 'n': // none
				obj = NONE;
				break;
			}
			ret->layout[i][j] = obj;
		}
	}

	return ret;
}
