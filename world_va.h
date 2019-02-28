#include "world_options.h"
#include <kos.h>

class WorldVA
{
public:
	WorldVA(WorldOptions wo);
	~WorldVA();
	vector_t**	verts();
	vector_t**	norms();
	vector_t**	texs();
	unsigned	strip_num();
	unsigned	strip_size();
private:
	vector_t** verts_;
	vector_t** norms_;
	vector_t** texs_; // texs for naming consistency ;)))))))))
	unsigned size_, tess_, vert_per_edge_, vert_count_;
	void build_world_();
};

