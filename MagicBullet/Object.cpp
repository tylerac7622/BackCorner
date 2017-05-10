#include "Object.h"

Object::Object(vector3 pos, vector3 rot)
{
	position = pos;
	eulerRotation = rot;
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));

	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}
Object::Object(vector3 pos, vector3 rot, String name)
{
	position = pos;
	eulerRotation = rot;
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));

	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
	modelName = name;
}

void Object::Reset(vector3 pos, vector3 rot)
{
	position = pos;
	eulerRotation = rot;
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));

	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}

Object::~Object(void)
{
}

void Object::Update(float globalTime)
{
	UpdateWorldMatrix();

	collider->SetModelMatrix(worldMatrix);
}

void Object::UpdateWorldMatrix(void)
{
	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}

vector3 Object::GetPosition(void) { return position; }
vector3 Object::GetEuler(void) { return eulerRotation; }
quaternion Object::GetRotation(void) { return rotation; }
matrix4 Object::GetWorldMatrix(void) { return worldMatrix; }
String Object::GetName(void) { return modelName; }

void Object::SetPosition(vector3 position2) { position = position2; }
void Object::SetRotation(quaternion rotation2) { }
void Object::SetWorldMatrix(matrix4 mat) { worldMatrix = mat; }

void Object::ChangeEuler(vector3 offset)
{
	eulerRotation += offset;
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * 0 / 180));
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));
}
void Object::ChangePosition(vector3 offset) { position += offset; }
void Object::ChangeRotation(quaternion offset) { }
