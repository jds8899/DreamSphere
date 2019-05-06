
#include "obj_renderer.h"
#include <kos.h>
#include <plx/matrix.h>
#include <plx/prim.h>
#include <stdio.h>
#include <kos/vector.h>

#include "utils.h"

/*
Private helper to buffer the faces for parallax to render
*/
void obj_submit_faces(ObjModel* obj, pvr_poly_hdr_t* hdr) {
	vector_t n = { 0,0,0,0 };

	//Iterate through each face
	int faceoffset = 0;
	for (int i = 0; i < obj->attrib.num_face_num_verts; i++) {
		int vertCnt = obj->attrib.face_num_verts[i];

		//pvr_list_begin(PVR_LIST_OP_POLY);
		pvr_prim(hdr, sizeof(pvr_poly_hdr_t));

		// Loop through all verticies of this face
		for (int j = faceoffset; j < faceoffset + vertCnt; j++) {
			tinyobj_vertex_index_t cur = obj->attrib.faces[j];

			float x = obj->attrib.vertices[cur.v_idx * 3],
				y = obj->attrib.vertices[cur.v_idx * 3 + 1],
				z = obj->attrib.vertices[cur.v_idx * 3 + 2];

			mat_trans_single(x, y, z);

			vector_t v = { x,y,z,1 };

			// End strip if this is last vert in face
			if (j == (faceoffset + vertCnt - 1))
				vertex_submit_black(n, n, v, n, n, true);
			else
				vertex_submit_black(n, n, v, n, n);
		}

		//pvr_list_finish();

		faceoffset += vertCnt;
	}
}


void obj_render(ObjModel* obj, pvr_poly_hdr_t* hdr) {

	//apply projection, world, and model matrices to PVR matrix.
	//does not affect matrices in PLX matrix registers, but will
	//affect the transformations on points for this model.
	plx_mat3d_apply_all();

	obj_submit_faces(obj, hdr);
}

void obj_render(ObjModel* obj, pvr_poly_hdr_t* hdr, point_t trans, vector_t rotate, vector_t scale)
{
	//assuming we are on PLX_MAT_MODELVIEW, perform transforms on a
	//new PLX matrix
	plx_mat3d_push();

	//Matrices applied in reverse order. Scale, translate, then rotate.
	//Rotation done last to provide smooth rotation when sonic turns.

	plx_mat3d_rotate(rotate.x, 1, 0, 0);
	plx_mat3d_rotate(rotate.y, 0, 1, 0);
	plx_mat3d_rotate(rotate.z, 0, 0, 1);

	plx_mat3d_translate(trans.x, trans.y, trans.z);

	plx_mat3d_scale(scale.x, scale.y, scale.z);

	//Do actual rendering
	obj_render(obj, hdr);

	//Undo matrix changes
	plx_mat3d_pop();
}