#include "world_options.h"


WorldOptions::WorldOptions(unsigned size, unsigned tess) :
	size_(size), 
	tess_(tess) {}


WorldOptions::~WorldOptions() {
}

unsigned WorldOptions::size() {
	return size_;
}

unsigned WorldOptions::tess() {
	return tess_;
}
