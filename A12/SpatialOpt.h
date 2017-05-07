#pragma once
#include "RE\ReEng.h"
#include "MyBOManager.h"

class SpatialOpt {
	public:
		SpatialOpt(float size, vector3 location, int numDivisions);
		void SetToDraw(bool value);
		bool GetToDraw();
		void GeneratePartionCenters();
		void DrawAllPartions();
		void CheckCollisions();
		void SetWorld(matrix4 a_m4ToWorld);


	private:
		matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
		MeshManagerSingleton* m_pMeshMngr = nullptr;//Mesh Manager Singleton
		MyBOManager* m_pBOMngr; //Pointer to Bounding Object Manager
		bool toDraw = true;
		bool isSoActive;
		float totalSize;
		float partitionSize;
		int numPartions;
		int divisions;
		vector3 center;
		std::vector<vector3> partionCenters;
};