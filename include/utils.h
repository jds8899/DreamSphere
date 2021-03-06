#ifndef VEC_UTILS_H
#define VEC_UTILS_H

#include <kos.h>
#include <plx/matrix.h>
#include <plx/prim.h>
#include <kos/vector.h>

void vertex_submit(vector_t light, vector_t light_vert, vector_t vert, vector_t norm, vector_t tex, bool eos = false);

void vertex_submit_black(vector_t light, vector_t light_vert, vector_t vert, vector_t norm, vector_t tex, bool eos = false);

/*
Loads and prints current working matrix used by parallax.

If pvr flag set to true, instead loads the direct matrix used by
PVR, which is wrapped by parallax.
*/
void print_current_matr(char* label, bool pvr=true);

pvr_poly_hdr_t create_nontextured_header(bool clockwise);

pvr_poly_hdr_t create_textured_header(pvr_ptr_t tex, unsigned height, unsigned width);

float fmod(float a, float b);

/*
Rotate a vector aroung y-axis by certain number of degrees.
Primary use is for turning calculations.

@param vec Input vector. Only X and Z components will be altered.
@param degrees Degrees to be rotating by

@return New vector that is rotated
*/
vector_t rotateAlongY(vector_t vec, float degrees);

#endif