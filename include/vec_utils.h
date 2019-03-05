#ifndef VEC_UTILS_H
#define VEC_UTILS_H

#include <kos.h>
#include <plx/matrix.h>
#include <plx/prim.h>

void vertex_submit(vector_t light, vector_t light_vert, vector_t vert, vector_t norm, vector_t tex, bool eos = false);

#endif