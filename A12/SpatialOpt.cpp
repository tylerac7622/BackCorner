#include "SpatialOpt.h"

SpatialOpt::SpatialOpt(float size, vector3 location, int numDivisions)
{
	totalSize = size;
	center = location;
	divisions = numDivisions;
}

void SpatialOpt::SetToDraw(bool value)
{
	toDraw = value;
}

bool SpatialOpt::GetToDraw()
{
	return toDraw;
}

