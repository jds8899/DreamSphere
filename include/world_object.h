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

	//Compiled texture header for this object
	pvr_poly_hdr_t header;
} WorldObject;

/*
Wrapper over obj_render that renders an object with
the proper world transformations. Uses gstate to determine
correct translation and rotation.

@param wobj The world object to render
*/
void world_object_render(WorldObject* wobj);

#endif
