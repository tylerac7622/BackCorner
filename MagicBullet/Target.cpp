#include "Target.h"

Target::Target(void)
{
	position = vector3(-30, 2, -70);
	eulerRotation = vector3(0, 0, 90.0f);
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));

	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}

void Target::Reset(void)
{
	position = vector3(-30, 2, -70);
	eulerRotation = vector3(0, 0, 90.0f);
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));

	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}

Target::~Target(void)
{
}

void Target::InitTarget(void)
{
	model = new PrimitiveClass();
	model->GenerateCylinder(2.0f, 0.5f, 10, REBLUE);
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
