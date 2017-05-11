#include "Target.h"

Target::Target(vector3 pos, vector3 rot, String name) : Object(pos, rot, name)
{
	active = true;
}
Target::Target(vector3 pos, vector3 rot) : Object(pos, rot, "targetblue")
{
	active = true;
}

Target::~Target(void)
{
}

void Target::Update(float globalTime)
{
	Object::Update(globalTime);
}

bool Target::IsActive(void) { return active; }

void Target::SetActive(bool act) { active = act; }
