
/*
Wrapper and struct over tinyobj OBJ file loading.
*/

#ifndef OBJ_MODEL_H
#define OBJ_MODEL_H

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "tinyobj_loader_c.h"

typedef struct {
	tinyobj_attrib_t attrib;
	tinyobj_shape_t* shapes = NULL;
	size_t num_shapes;
	tinyobj_material_t* materials = NULL;
	size_t num_materials;
} ObjModel;

/*
Launch file into raw byte buffer. 
Caller must free buffer.

Code used from https://stackoverflow.com/a/36547932/7691601

@param path Filepatj
@param data_length Out variable reference; specifies length of byte buffer

@return Byte buffer of file
*/
char* load_file(char const* path, size_t* data_length);

/*
Retrieve and construct an object model from a given file path.

Caller responsible for freeing resources.
*/
ObjModel* obj_get(char const* path);

/*
Free object resources.
*/
void obj_cleanup(ObjModel* obj);

/*
Print out fields of tinyobj attrib (incomplete)
*/
void print_tiny_attrib(tinyobj_attrib_t a);

#endif
