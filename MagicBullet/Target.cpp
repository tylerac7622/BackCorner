#include "Target.h"

Target::Target(vector3 pos, vector3 rot)
{
	position = pos;
	eulerRotation = rot;
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));

	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}

void Target::Reset(vector3 pos)
{
	position = pos;
	eulerRotation = vector3(0, 0, 90.0f);
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));

	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}

Target::~Target(void)
{
}

void Target::InitTarget(vector3 siz, String nam)
{
	modelName = nam;
	model = new PrimitiveClass();

	model->GenerateCuboid(siz, REGRAY);
	size = siz;

	//m_pCone->LoadModel("bullet.obj", "bullet");

	collider = new MyBoundingBoxClass(model->GetVertexList());
	collider->SetColliding(false);
}
void Target::InitTarget(vector2 size, String nam)
{
	modelName = nam;
	model = new PrimitiveClass();

	model->GenerateCylinder(size.x, size.y, 10, REBLUE);
	//m_pCone->LoadModel("bullet.obj", "bullet");

	collider = new MyBoundingBoxClass(model->GetVertexList());
	collider->SetColliding(false);
}

void Target::Update(float globalTime)
{
	UpdateWorldMatrix();

	collider->SetModelMatrix(worldMatrix);
}

void Target::UpdateWorldMatrix(void)
{
	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}

vector3 Target::GetPosition(void) { return position; }
vector3 Target::GetEuler(void) { return eulerRotation; }
vector3 Target::GetSize(void) { return size; }
String Target::GetName(void) { return modelName; }
quaternion Target::GetRotation(void) { return rotation; }
matrix4 Target::GetWorldMatrix(void) { return worldMatrix; }

void Target::SetPosition(vector3 position2) { position = position2; }
void Target::SetRotation(quaternion rotation2) { }
void Target::SetEuler(vector3 euler2) { eulerRotation = euler2;  }
void Target::SetWorldMatrix(matrix4 mat) { worldMatrix = mat; }

void Target::ChangeEuler(vector3 offset)
{
	eulerRotation += offset;
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));
}
void Target::ChangePosition(vector3 offset) { position += offset; }
void Target::ChangeRotation(quaternion offset) { }
