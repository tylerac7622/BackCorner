#pragma once
#include "RE\ReEng.h"
#include "MyBoundingBox.h"
#include "Target.h"

using namespace ReEng;

class SpatialOpt {
	public:
		std::vector<Object*> content;
		std::vector<SpatialOpt> subdivisions;
		MyBoundingBoxClass* collider;

		SpatialOpt(float size, vector3 location, int numDivisions);
		void SetToDraw(bool value);
		bool GetToDraw();
		void GeneratePartionCenters();
		void DrawAllPartions();
		void PlaceObject(Object* toPlace);
		void GetPlacement(Object* toPlace);
		void SetWorld(matrix4 a_m4ToWorld);
		void ClearTree();
		void Recreate(float size, vector3 location, int numDivisions);


	private:
		matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
		MeshManagerSingleton* m_pMeshMngr = nullptr;//Mesh Manager Singleton
		bool toDraw = true;
		bool isSoActive;
		float totalSize;
		float partitionSize;
		int numPartions;
		int divisions;
		vector3 center;
		std::vector<vector3> partionCenters;
};