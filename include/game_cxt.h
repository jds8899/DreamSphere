#ifndef GAME_CXT_H
#define GAME_CXT_H

#include <kos.h>
#include <plx/matrix.h>
#include <plx/prim.h>
#include <png/png.h>

#include "utils.h"
#include "world_va.h"
#include "world_options.h"
#include "game_logic.h"

#define DEBUG_GAME

void game_cxt_init();

void game_cxt_prep();

void game_cxt_render();

void game_cxt_cleanup();

#endif

