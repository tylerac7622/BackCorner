#include "Target.h"

Target::Target(vector3 pos, vector3 rot) : Object(pos, rot, "target")
{
}

Target::~Target(void)
{
}

void Target::Update(float globalTime)
{
	Object::Update(globalTime);
}
