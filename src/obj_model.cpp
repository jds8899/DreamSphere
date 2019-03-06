
#include <kos.h>
#include <stdio.h>
#include <stdlib.h>

#include "obj_model.h"

//#define TINYOBJ_LOADER_C_IMPLEMENTATION
//#include "tinyobj_loader_c.h"

char* load_file(char const* path, size_t* data_length) {
	char* buffer = 0;
	long length;
	FILE * f = fopen(path, "rb"); //was "rb"

	if (f)
	{
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);
		buffer = (char*)malloc((length + 1) * sizeof(char));
		if (buffer)
		{
			fread(buffer, sizeof(char), length, f);
		}
		fclose(f);
	}
	buffer[length] = '\0';
	// for (int i = 0; i < length; i++) {
	//     printf("buffer[%d] == %c\n", i, buffer[i]);
	// }
	//printf("buffer = %s\n", buffer);

	*data_length = length;
	return buffer;
}

ObjModel* obj_get(char const* path) {
	tinyobj_attrib_t attrib;
	tinyobj_shape_t* shapes = NULL;
	size_t num_shapes;
	tinyobj_material_t* materials = NULL;
	size_t num_materials;

	size_t data_len = 0;

	// Read file
	char* data_buffer = load_file(path, &data_len);

	// No clue but this was in the example
	unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;

	// Have tinyobj parse the file. It automatically parses the MTL file(s) too
	int res = tinyobj_parse_obj(&attrib, &shapes, &num_shapes, &materials,
		&num_materials, data_buffer, data_len, flags);

	printf("%s\n", data_buffer);
	//Free byte buffer as we no longer need it
	free(data_buffer);
	
	//Report and return null if error
	if (res != TINYOBJ_SUCCESS) {
		printf("Tinyobj loading error, error code %i. Exiting object loader.\n", res);
		return 0;
	}

	//Condense into a struct and return
	ObjModel* obj = (ObjModel*)malloc(sizeof(ObjModel));
	obj->attrib = attrib;
	obj->shapes = shapes;
	obj->num_shapes = num_shapes;
	obj->materials = materials;
	obj->num_materials = num_materials;

	return obj;
}

void obj_cleanup(ObjModel* obj) {
	tinyobj_attrib_free(&obj->attrib);
	tinyobj_shapes_free(obj->shapes, obj->num_shapes);
	tinyobj_materials_free(obj->materials, obj->num_materials);

	free(obj);
}

/*
typedef struct {
  unsigned int num_vertices;
  unsigned int num_normals;
  unsigned int num_texcoords;
  unsigned int num_faces;
  unsigned int num_face_num_verts;

  int pad0;

  float *vertices;
  float *normals;
  float *texcoords;
  tinyobj_vertex_index_t *faces;
  int *face_num_verts;
  int *material_ids;
} tinyobj_attrib_t;
*/
void print_tiny_attrib(tinyobj_attrib_t a) {
	printf(
		"tinyobj_attrib{\n"
		"#verts: %i\n"
		"#norms: %i\n"
		"#texcoords: %i\n"
		"#faces: %i\n"
		"#faceverts: %i\n"
		"pad: %i\n",
		a.num_vertices, a.num_normals, a.num_texcoords, a.num_faces, a.num_face_num_verts, a.pad0
	);

	printf("verts: [");
	for (int i = 0; i < a.num_vertices; i++) {
		printf("%f,", a.vertices[i]);
	}

	printf("]\nnormals: [");
	for (int i = 0; i < a.num_normals; i++) {
		printf("%f,", a.normals[i]);
	}

	printf("]\ntexcoords: [");
	for (int i = 0; i < a.num_texcoords; i++) {
		printf("%f,", a.texcoords[i]);
	}

	printf("]\n");

	//incomplete

	printf("}\n");
}
