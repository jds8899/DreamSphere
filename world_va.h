#include "world_options.h"
#include "vertex.h"
#include <kos.h>

class WorldVA
{
public:
	WorldVA(WorldOptions wo);
	~WorldVA();
	Vertex** wva();
private:
	Vertex** wva_;
	unsigned size_, tess_, vert_per_edge_, vert_count_;
	void build_world_();
};

