/*
Handle rendering of OBJ model files.
*/

#ifndef OBJ_RENDERER_H
#define OBJ_RENDERER_H

#include "obj_model.h"

#include <kos.h>
#include "vertex.h"

/*
Render a model in the current scene. 
Assumes the scene has already begun and PVR/PLX has been initialized.
Renders each face as an independent strip. (TODO: Improve this?)
*/
void obj_render(ObjModel* obj, pvr_poly_hdr_t* hdr);

//void obj_render(ObjModel* obj, vector_t pos, vector_t scale, vector_t rot);

#endif

