#pragma once
#include "RE\ReEng.h"

class SpatialOpt {
	public:
		SpatialOpt(float size, vector3 location, int numDivisions);
		void SetToDraw(bool value);
		bool GetToDraw();


	private:
		bool toDraw;
		float totalSize;
		float partitionSize;
		int numPartions;
		int divisions;
		vector3 center;
};