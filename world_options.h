#pragma once
class WorldOptions
{
public:
	WorldOptions(unsigned size, unsigned tess);
	~WorldOptions();
	unsigned size();
	unsigned tess();
private:
	unsigned size_, tess_;
};

