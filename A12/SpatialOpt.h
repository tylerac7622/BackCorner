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



	private:
		MyBOManager* m_pBOMngr; //Pointer to Bounding Object Manager
		bool toDraw;
		bool isSoActive;
		float totalSize;
		float partitionSize;
		int numPartions;
		int divisions;
		vector3 center;
		std::vector<vector3> partionCenters;
};