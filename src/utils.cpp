#include "utils.h"

void vertex_submit(vector_t light, vector_t light_vert, vector_t vert, vector_t norm, vector_t tex, bool eos) {
	int flags = eos ? PVR_CMD_VERTEX_EOL : PVR_CMD_VERTEX;

	//printf("flag: %d, x:%f, y:%f, z:%f\n", flags, vert.x, vert.y, vert.z);
	plx_vert_ffp(flags, vert.x, vert.y, vert.z, 1, 1, 1, 1, tex.x, tex.y);
}

pvr_poly_hdr_t create_nontextured_header() {
	pvr_poly_hdr_t nontextured_header;
	pvr_poly_cxt_t nontextured_context;
	pvr_poly_cxt_col(&nontextured_context, PVR_LIST_OP_POLY);
	nontextured_context.gen.culling = PVR_CULLING_CCW;
	pvr_poly_compile(&nontextured_header, &nontextured_context);
	return nontextured_header;
}

pvr_poly_hdr_t create_textured_header(pvr_ptr_t tex, unsigned height, unsigned width) {
	pvr_poly_hdr_t hdr;
	pvr_poly_cxt_t cxt;
	pvr_poly_cxt_txr(&cxt, PVR_LIST_OP_POLY, PVR_TXRFMT_RGB565, height, width, tex, PVR_FILTER_NONE);

	cxt.gen.culling = PVR_CULLING_CCW;
	pvr_poly_compile(&hdr, &cxt);
	return hdr;
}

int floor(float x) { 
	int i = x - 2;
	while (++i <= x - 1);
	return i;
}

float fmod(float a, float b) {
	return (a - b * (float)floor(a / b));
}
