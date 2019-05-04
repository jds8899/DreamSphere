/*
Handle rendering of OBJ model files.
*/

#ifndef OBJ_RENDERER_H
#define OBJ_RENDERER_H

#include "obj_model.h"

#include <kos.h>
#include "vertex.h"

/*
Render a model in the current scene with no transformations.
Assumes the scene has already begun and PVR/PLX has been initialized.
Renders each face as an independent strip. (TODO: Improve this?)
Merely applies view matrices then renders faces.

@param obj The loaded OBJ file of object model
@param hdr Texture header for object
*/
void obj_render(ObjModel* obj, pvr_poly_hdr_t* hdr);

/*
Render a model in the current scene with no transformations.
Same assumptions as overloaded obj_render().
After applying view matrices, push a new model matrix and apply that to
the current matrix.

@param trans Translation of object
@param rotate Rotation in degrees along each of X, Y, and Z axes
@param scale Scale of object
*/
void obj_render(ObjModel* obj, pvr_poly_hdr_t* hdr, point_t trans, vector_t rotate, vector_t scale);

#endif

