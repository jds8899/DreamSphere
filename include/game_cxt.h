#ifndef GAME_CXT_H
#define GAME_CXT_H

#include <kos.h>
#include <plx/matrix.h>
#include <plx/prim.h>

#include "vec_utils.h"
#include "world_va.h"
#include "world_options.h"

void game_cxt_init();

void game_cxt_prep();

void game_cxt_render(pvr_poly_hdr_t* hdr);

void game_cxt_cleanup();

#endif

