 #include "SpatialOpt.h"
#include <stdio.h>      /* printf */
#include <math.h>

SpatialOpt::SpatialOpt(float size, vector3 location, int numDivisions)
{
	totalSize = size;
	center = location;
	divisions = numDivisions;

	numPartions = numDivisions * 8;
	partitionSize = totalSize / numPartions;
	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	if (numDivisions > 0)
	{
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x + (size / 4), location.y + (size / 4), location.z + (size / 4)), numDivisions - 1));
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x - (size / 4), location.y + (size / 4), location.z + (size / 4)), numDivisions - 1));
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x + (size / 4), location.y - (size / 4), location.z + (size / 4)), numDivisions - 1));
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x - (size / 4), location.y - (size / 4), location.z + (size / 4)), numDivisions - 1));
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x + (size / 4), location.y + (size / 4), location.z - (size / 4)), numDivisions - 1));
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x - (size / 4), location.y + (size / 4), location.z - (size / 4)), numDivisions - 1));
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x + (size / 4), location.y - (size / 4), location.z - (size / 4)), numDivisions - 1));
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x - (size / 4), location.y - (size / 4), location.z - (size / 4)), numDivisions - 1));
	}
	else
	{
		subdivisions.clear();
	}

	std::vector<vector3> colliderPoints;
	colliderPoints.push_back(vector3(vector3(location.x + (size / 2), location.y + (size / 2), location.z + (size / 2))));
	colliderPoints.push_back(vector3(vector3(location.x - (size / 2), location.y + (size / 2), location.z + (size / 2))));
	colliderPoints.push_back(vector3(vector3(location.x + (size / 2), location.y - (size / 2), location.z + (size / 2))));
	colliderPoints.push_back(vector3(vector3(location.x - (size / 2), location.y - (size / 2), location.z + (size / 2))));
	colliderPoints.push_back(vector3(vector3(location.x + (size / 2), location.y + (size / 2), location.z - (size / 2))));
	colliderPoints.push_back(vector3(vector3(location.x - (size / 2), location.y + (size / 2), location.z - (size / 2))));
	colliderPoints.push_back(vector3(vector3(location.x + (size / 2), location.y - (size / 2), location.z - (size / 2))));
	colliderPoints.push_back(vector3(vector3(location.x - (size / 2), location.y - (size / 2), location.z - (size / 2))));
	collider = new MyBoundingBoxClass(colliderPoints);
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
	//	toPush.x = -totalSize/2 + ((x + 1) * partitionSize) - (partitionSize / 2);
		//toPush.x = ((center.x - totalSize/2) +  (x + 1) * partitionSize) - (partitionSize / 2);

		for (int y = 0; y < std::cbrt(numPartions); y++) {
			toPush.y = ((y + 1) * partitionSize) - (partitionSize / 2);
		//	toPush.y = -totalSize/2 + ((y + 1) * partitionSize) - (partitionSize / 2);
		//	toPush.y = ((center.y - totalSize / 2) + (y + 1) * partitionSize) - (partitionSize / 2);

			for (int z= 0; z < std::cbrt(numPartions); z++) {
				toPush.z = ((z + 1) * partitionSize) - (partitionSize / 2);
			//	toPush.z = -totalSize/2 + ((z + 1) * partitionSize) - (partitionSize / 2);
			//	toPush.z = ((center.z - totalSize / 2) + (z + 1) * partitionSize) - (partitionSize / 2);
				partionCenters.push_back(toPush);
			}
		}
	}
}

void SpatialOpt::PlaceObject(Target* toPlace)
{
	int colliding = -1;
	if (subdivisions.size() == 0)
	{
		content.push_back(toPlace);
		toPlace->currentSpec.push_back(this);
	}
	for (int i = 0; i < subdivisions.size(); i++)
	{
		bool isCollide = toPlace->collider->IsColliding(subdivisions[i].collider);
		if (isCollide)
		{
			subdivisions[i].PlaceObject(toPlace);
		}
	}

	if (colliding != -1)
	{
		subdivisions[colliding].PlaceObject(toPlace);
	}
}

void SpatialOpt::ClearTree()
{
	content.clear();
	for (int i = 0; i < subdivisions.size(); i++) {
		subdivisions[i].ClearTree();
	}
}
void SpatialOpt::Recreate(float size, vector3 location, int numDivisions)
{
	ClearTree();

	totalSize = size;
	center = location;
	divisions = numDivisions;

	numPartions = numDivisions * 8;
	partitionSize = totalSize / numPartions;
	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	subdivisions.clear();
	if (numDivisions > 0)
	{
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x + (size / 4), location.y + (size / 4), location.z + (size / 4)), numDivisions - 1));
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x - (size / 4), location.y + (size / 4), location.z + (size / 4)), numDivisions - 1));
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x + (size / 4), location.y - (size / 4), location.z + (size / 4)), numDivisions - 1));
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x - (size / 4), location.y - (size / 4), location.z + (size / 4)), numDivisions - 1));
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x + (size / 4), location.y + (size / 4), location.z - (size / 4)), numDivisions - 1));
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x - (size / 4), location.y + (size / 4), location.z - (size / 4)), numDivisions - 1));
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x + (size / 4), location.y - (size / 4), location.z - (size / 4)), numDivisions - 1));
		subdivisions.push_back(SpatialOpt(size / 2, vector3(location.x - (size / 4), location.y - (size / 4), location.z - (size / 4)), numDivisions - 1));
	}

	std::vector<vector3> colliderPoints;
	colliderPoints.push_back(vector3(vector3(location.x + (size / 2), location.y + (size / 2), location.z + (size / 2))));
	colliderPoints.push_back(vector3(vector3(location.x - (size / 2), location.y + (size / 2), location.z + (size / 2))));
	colliderPoints.push_back(vector3(vector3(location.x + (size / 2), location.y - (size / 2), location.z + (size / 2))));
	colliderPoints.push_back(vector3(vector3(location.x - (size / 2), location.y - (size / 2), location.z + (size / 2))));
	colliderPoints.push_back(vector3(vector3(location.x + (size / 2), location.y + (size / 2), location.z - (size / 2))));
	colliderPoints.push_back(vector3(vector3(location.x - (size / 2), location.y + (size / 2), location.z - (size / 2))));
	colliderPoints.push_back(vector3(vector3(location.x + (size / 2), location.y - (size / 2), location.z - (size / 2))));
	colliderPoints.push_back(vector3(vector3(location.x - (size / 2), location.y - (size / 2), location.z - (size / 2))));
	collider = new MyBoundingBoxClass(colliderPoints);
}

void SpatialOpt::DrawAllPartions()
{
	if (!toDraw) { return; }

	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_m4ToWorld, center) *
		glm::scale(vector3(totalSize, totalSize, totalSize)), RERED, WIRE);
	for (int i = 0; i < subdivisions.size(); i++) {
		subdivisions[i].DrawAllPartions();
	}

	/*for (int i = 0; i < numPartions; i++) {
	//	m_pMeshMngr->AddCubeToRenderList(m_m4ToWorld, REGREEN);
		m_pMeshMngr->AddCubeToRenderList(glm::translate(m_m4ToWorld, partionCenters[i]) *
			glm::scale(vector3(partitionSize, partitionSize, partitionSize)), RERED, WIRE);
	}*/
}

void SpatialOpt::SetWorld(matrix4 a_m4ToWorld)
{
	m_m4ToWorld = a_m4ToWorld;
}

