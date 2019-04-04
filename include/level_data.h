#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

#include <kos.h>
#include "world_options.h"

enum ObjectType_t {BLUE, RED, BUMP, RING, NONE};

typedef struct {
	WorldOptions* wo;
	ObjectType_t** layout;
} LevelData_t;

LevelData_t* read_level(const char* path);

#endif