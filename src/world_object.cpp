
#include "world_object.h"
#include "game_logic.h"
#include "utils.h"
#include "obj_renderer.h"
#include <kos.h>

void world_object_render(WorldObject* wobj)
{
	//vector_t scal = { 0.5,0.5,0.5,0.0 };

	float x0 = 0.0, z0 = 0.0;

	float objXpos = (wobj->pos.x - gstate->xpos);
	float objYpos = wobj->pos.y;
	float objZpos = (wobj->pos.z - gstate->zpos);

	//wrap object around if it's more than "halfway" around the world
	float half = gstate->level_width / 2;

	if (objXpos < (-1)*half) objXpos += gstate->level_width;
	if (objXpos > half) objXpos -= gstate->level_width;

	if (objZpos < (-1)*half) objZpos += gstate->level_width;
	if (objZpos > half) objZpos -= gstate->level_width;

	//Convert to world space, as units are currently in level space.
	//Z inverted since +z is towards camera
	objXpos *= gstate->level_to_world_space;
	objZpos *= gstate->level_to_world_space;
	objZpos *= (-1);

	point_t tran = { objXpos,objYpos,objZpos , 0 };
	vector_t rot = { wobj->rot.x, wobj->rot.y + gstate->sonic_turn_degrees, wobj->rot.z,  0 };

	obj_render(wobj->model, &(wobj->header), tran, rot, wobj->scale);
}
