
#include "obj_renderer.h"
#include <kos.h>
#include <plx/matrix.h>
#include <plx/prim.h>

#include "vec_utils.h"

void obj_render(ObjModel* obj, pvr_poly_hdr_t* hdr) {

	plx_mat3d_push();
	plx_mat3d_identity();
	plx_mat3d_translate(0, 0, -2);
	//plx_mat3d_apply_all();

	vector_t n = { 0,0,0,0 };

	//Iterate through each face
	int faceoffset = 0;
	for (int i = 0; i < obj->attrib.num_face_num_verts; i++) {
		int vertCnt = obj->attrib.face_num_verts[i];

		//pvr_list_begin(PVR_LIST_OP_POLY);
		//pvr_prim(hdr, sizeof(pvr_poly_hdr_t));

		// Loop through all verticies of this face
		for (int j = faceoffset; j < faceoffset + vertCnt; j++) {
			tinyobj_vertex_index_t cur = obj->attrib.faces[j];

			float x = obj->attrib.vertices[cur.v_idx],
				y = obj->attrib.vertices[cur.v_idx + 1],
				z = obj->attrib.vertices[cur.v_idx + 2];

			mat_trans_single(x, y, z);

			vector_t v = { x,y,z,1};

			// End strip if this is last vert in face
			if(j == (faceoffset+vertCnt -1))
				vertex_submit_black(n, n, v, n, n, true);
			else
				vertex_submit_black(n, n, v, n, n);
		}

		//pvr_list_finish();

		faceoffset += vertCnt;
	}

	plx_mat3d_pop();
}

