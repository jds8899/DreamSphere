/*
Converted version of tinyobj library to link as normal code instead of compiling
inline. Had to do that to prevent linking headaches...
*/


/*
   The MIT License (MIT)

   Copyright (c) 2016 Syoyo Fujita and many contributors.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
   */
#ifndef TINOBJ_LOADER_C_H_
#define TINOBJ_LOADER_C_H_

/* @todo { Remove stddef dependency. size_t? } */
#include <stddef.h>

typedef struct {
  char *name;

  float ambient[3];
  float diffuse[3];
  float specular[3];
  float transmittance[3];
  float emission[3];
  float shininess;
  float ior;      /* index of refraction */
  float dissolve; /* 1 == opaque; 0 == fully transparent */
  /* illumination model (see http://www.fileformat.info/format/material/) */
  int illum;

  int pad0;

  char *ambient_texname;            /* map_Ka */
  char *diffuse_texname;            /* map_Kd */
  char *specular_texname;           /* map_Ks */
  char *specular_highlight_texname; /* map_Ns */
  char *bump_texname;               /* map_bump, bump */
  char *displacement_texname;       /* disp */
  char *alpha_texname;              /* map_d */
} tinyobj_material_t;

typedef struct {
  char *name; /* group name or object name. */
  unsigned int face_offset;
  unsigned int length;
} tinyobj_shape_t;

typedef struct { int v_idx, vt_idx, vn_idx; } tinyobj_vertex_index_t;

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


#define TINYOBJ_FLAG_TRIANGULATE (1 << 0)

#define TINYOBJ_INVALID_INDEX (0x80000000)

#define TINYOBJ_SUCCESS (0)
#define TINYOBJ_ERROR_EMPTY (-1)
#define TINYOBJ_ERROR_INVALID_PARAMETER (-2)
#define TINYOBJ_ERROR_FILE_OPERATION (-3)

/* Parse wavefront .obj(.obj string data is expanded to linear char array `buf')
 * flags are combination of TINYOBJ_FLAG_***
 * Returns TINYOBJ_SUCCESS if things goes well.
 * Returns TINYOBJ_ERR_*** when there is an error.
 */
//extern int tinyobj_parse_obj(tinyobj_attrib_t *attrib, tinyobj_shape_t **shapes,
//                             size_t *num_shapes, tinyobj_material_t **materials,
//                             size_t *num_materials, const char *buf, size_t len,
//                             unsigned int flags);
//extern int tinyobj_parse_mtl_file(tinyobj_material_t **materials_out,
//                                  size_t *num_materials_out,
//                                  const char *filename);
//
//extern void tinyobj_attrib_init(tinyobj_attrib_t *attrib);
//extern void tinyobj_attrib_free(tinyobj_attrib_t *attrib);
//extern void tinyobj_shapes_free(tinyobj_shape_t *shapes, size_t num_shapes);
//extern void tinyobj_materials_free(tinyobj_material_t *materials,
//                                   size_t num_materials);

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#if defined(TINYOBJ_MALLOC) && defined(TINYOBJ_REALLOC) && defined(TINYOBJ_CALLOC) && defined(TINYOBJ_FREE)
/* ok */
#elif !defined(TINYOBJ_MALLOC) && !defined(TINYOBJ_REALLOC) && !defined(TINYOBJ_CALLOC) && !defined(TINYOBJ_FREE)
/* ok */
#else
#error "Must define all or none of TINYOBJ_MALLOC, TINYOBJ_REALLOC, TINYOBJ_CALLOC and TINYOBJ_FREE."
#endif

#ifndef TINYOBJ_MALLOC
#include <stdlib.h>
#define TINYOBJ_MALLOC malloc
#define TINYOBJ_REALLOC realloc
#define TINYOBJ_CALLOC calloc
#define TINYOBJ_FREE free
#endif

#define TINYOBJ_MAX_FACES_PER_F_LINE (16)

#define IS_SPACE(x) (((x) == ' ') || ((x) == '\t'))
#define IS_DIGIT(x) ((unsigned int)((x) - '0') < (unsigned int)(10))
#define IS_NEW_LINE(x) (((x) == '\r') || ((x) == '\n') || ((x) == '\0'))

//static void skip_space(const char **token);

//static void skip_space_and_cr(const char **token);

//static int until_space(const char *token);

//static size_t length_until_newline(const char *token, size_t n);

//static size_t length_until_line_feed(const char *token, size_t n);

/* http://stackoverflow.com/questions/5710091/how-does-atoi-function-in-c-work
*/
//static int my_atoi(const char *c);

/* Make index zero-base, and also support relative index. */
//static int fixIndex(int idx, size_t n);

/* Parse raw triples: i, i/j/k, i//k, i/j */
//static tinyobj_vertex_index_t parseRawTriple(const char **token);

//static int parseInt(const char **token);

/*
 * Tries to parse a floating point number located at s.
 *
 * s_end should be a location in the string where reading should absolutely
 * stop. For example at the end of the string, to prevent buffer overflows.
 *
 * Parses the following EBNF grammar:
 *   sign    = "+" | "-" ;
 *   END     = ? anything not in digit ?
 *   digit   = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
 *   integer = [sign] , digit , {digit} ;
 *   decimal = integer , ["." , integer] ;
 *   float   = ( decimal , END ) | ( decimal , ("E" | "e") , integer , END ) ;
 *
 *  Valid strings are for example:
 *   -0  +3.1417e+2  -0.0E-3  1.0324  -1.41   11e2
 *
 * If the parsing is a success, result is set to the parsed value and true
 * is returned.
 *
 * The function is greedy and will parse until any of the following happens:
 *  - a non-conforming character is encountered.
 *  - s_end is reached.
 *
 * The following situations triggers a failure:
 *  - s >= s_end.
 *  - parse failure.
 */
//static int tryParseDouble(const char *s, const char *s_end, double *result);

//static float parseFloat(const char **token);

//static void parseFloat2(float *x, float *y, const char **token);

//static void parseFloat3(float *x, float *y, float *z, const char **token);

//static char *my_strdup(const char *s, size_t max_length);

//static char *my_strndup(const char *s, size_t len);

//static void initMaterial(tinyobj_material_t *material);

/* Implementation of string to int hashtable */

#define HASH_TABLE_ERROR 1 
#define HASH_TABLE_SUCCESS 0

#define HASH_TABLE_DEFAULT_SIZE 10

typedef struct hash_table_entry_t
{
  unsigned long hash;
  int filled;
  int pad0;
  long value;

  struct hash_table_entry_t* next;
} hash_table_entry_t;

typedef struct
{
  unsigned long* hashes;
  hash_table_entry_t* entries;
  size_t capacity;
  size_t n;
} hash_table_t;

//static unsigned long hash_djb2(const unsigned char* str);

//static void create_hash_table(size_t start_capacity, hash_table_t* hash_table);

//static void destroy_hash_table(hash_table_t* hash_table);

/* Insert with quadratic probing */
//static int hash_table_insert_value(unsigned long hash, long value, hash_table_t* hash_table);

//static int hash_table_insert(unsigned long hash, long value, hash_table_t* hash_table);

//static hash_table_entry_t* hash_table_find(unsigned long hash, hash_table_t* hash_table);

//static void hash_table_maybe_grow(size_t new_n, hash_table_t* hash_table);

//static int hash_table_exists(const char* name, hash_table_t* hash_table);

//static void hash_table_set(const char* name, size_t val, hash_table_t* hash_table);

//static long hash_table_get(const char* name, hash_table_t* hash_table);

//static tinyobj_material_t *tinyobj_material_add(tinyobj_material_t *prev,
//	size_t num_materials,
//	tinyobj_material_t *new_mat);
//
//static int tinyobj_parse_and_index_mtl_file(tinyobj_material_t **materials_out,
//	size_t *num_materials_out,
//	const char *filename,
//	hash_table_t* material_table);

int tinyobj_parse_mtl_file(tinyobj_material_t **materials_out,
	size_t *num_materials_out,
	const char *filename);


typedef enum {
  COMMAND_EMPTY,
  COMMAND_V,
  COMMAND_VN,
  COMMAND_VT,
  COMMAND_F,
  COMMAND_G,
  COMMAND_O,
  COMMAND_USEMTL,
  COMMAND_MTLLIB

} CommandType;

typedef struct {
  float vx, vy, vz;
  float nx, ny, nz;
  float tx, ty;

  /* @todo { Use dynamic array } */
  tinyobj_vertex_index_t f[TINYOBJ_MAX_FACES_PER_F_LINE];
  size_t num_f;

  int f_num_verts[TINYOBJ_MAX_FACES_PER_F_LINE];
  size_t num_f_num_verts;

  const char *group_name;
  unsigned int group_name_len;
  int pad0;

  const char *object_name;
  unsigned int object_name_len;
  int pad1;

  const char *material_name;
  unsigned int material_name_len;
  int pad2;

  const char *mtllib_name;
  unsigned int mtllib_name_len;

  CommandType type;
} Command;

//static int parseLine(Command *command, const char *p, size_t p_len,
//	int triangulate);

typedef struct {
  size_t pos;
  size_t len;
} LineInfo;

//static int is_line_ending(const char *p, size_t i, size_t end_i);

int tinyobj_parse_obj(tinyobj_attrib_t *attrib, tinyobj_shape_t **shapes,
	size_t *num_shapes, tinyobj_material_t **materials_out,
	size_t *num_materials_out, const char *buf, size_t len,
	unsigned int flags);

void tinyobj_attrib_init(tinyobj_attrib_t *attrib);

void tinyobj_attrib_free(tinyobj_attrib_t *attrib);

void tinyobj_shapes_free(tinyobj_shape_t *shapes, size_t num_shapes);

void tinyobj_materials_free(tinyobj_material_t *materials,
	size_t num_materials);

#endif /* TINOBJ_LOADER_C_H_ */
