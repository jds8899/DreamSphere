/*
Manage the state of an object placed in the world
*/

#ifndef WORLD_OBJ_H
#define WORLD_OBJ_H

#include "obj_model.h"

#include <kos.h>
#include <kos/vector.h>

typedef struct {

	//Absolute position in level space
	point_t pos;

	//Rotation of obj in degrees along each axis
	vector_t rot;

	//Scale of model
	vector_t scale;

	//Pointer to 3D model of object for rendering.
	//Initializer of object responsible for its memory
	ObjModel* model;
} WorldObject;

#endif
