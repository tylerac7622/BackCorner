#include "SpatialOpt.h"
#include <stdio.h>      /* printf */
#include <math.h>   

SpatialOpt::SpatialOpt(float size, vector3 location, int numDivisions)
{
	totalSize = size;
	center = location;
	divisions = numDivisions;
	m_pBOMngr = MyBOManager::GetInstance();

	numPartions = numDivisions * 8;
	partitionSize = totalSize / numPartions;
}

void SpatialOpt::SetToDraw(bool value)
{
	toDraw = value;
}

bool SpatialOpt::GetToDraw()
{
	return toDraw;
}

void SpatialOpt::GeneratePartionCenters()
{
	vector3 toPush = vector3(0.0f, 0.0f, 0.0f);

	for (int x = 0; x < std::cbrt(numPartions); x++) {
		toPush.x = ((x + 1) * partitionSize) - (partitionSize / 2);

		for (int y = 0; y < std::cbrt(numPartions); y++) {
			toPush.y = ((y + 1) * partitionSize) - (partitionSize / 2);

			for (int z= 0; z < std::cbrt(numPartions); z++) {
				toPush.z = ((z + 1) * partitionSize) - (partitionSize / 2);
				partionCenters.push_back(toPush);
			}
		}
	}
}

