#include "level_data.h"

LevelData_t* read_level(const char* path) {
	LevelData_t* ret = (LevelData_t*)malloc(sizeof(LevelData_t));
	ret->wo = (WorldOptions*)malloc(sizeof(WorldOptions));

	FILE* f = fopen(path, "rb"); // was "rb"
	int size, tess;
	fscanf(f, "%d", &size);
	fscanf(f, "%d", &tess);
	ret->wo->size = size;
	ret->wo->tess = tess;

	ret->layout = (ObjectType_t**)malloc(sizeof(ObjectType_t*) * size);

	char read;
	ObjectType_t obj;
	for (int i = 0; i < size; ++i) {
		ret->layout[i] = (ObjectType_t*)malloc(sizeof(ObjectType_t) * size);
		for (int j = 0; j < size; ++j) {
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
