#pragma once

#include "RE\ReEng.h"
#include "MyBOClass.h"

using namespace ReEng;

class SpatialOpt;

class SpatOptObj {
	public:
		vector3 position;
		MyBOClass* collider;
		String name;
		SpatialOpt* currentSpec;

		SpatOptObj(String name, vector3 position);
};