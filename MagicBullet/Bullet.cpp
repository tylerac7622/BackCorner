#include "Bullet.h"

Bullet::Bullet(vector3 pos, vector3 rot)
{
	position = pos;
	velocity = 20.0f;
	eulerRotation = rot;
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));
	forward = rotation * vector3(0, 0, -1);
	rotationSpeed = vector3(0, 0, 0);

	bulletCam.SetPosition(vector3(0.0f, 0.0f, 15.0f));
	bulletCam.SetTarget(ZERO_V3);
	bulletCam.SetUp(REAXISY);

	isFired = false;

	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}

void Bullet::Reset(vector3 pos, vector3 rot)
{
	position = pos;
	velocity = 20.0f;
	eulerRotation = rot;
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));
	forward = rotation * vector3(0, 0, -1);
	rotationSpeed = vector3(0, 0, 0);

	bulletCam.SetPosition(vector3(0.0f, 0.0f, 15.0f));
	bulletCam.SetTarget(ZERO_V3);
	bulletCam.SetUp(REAXISY);

	isFired = false;

	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}

Bullet::~Bullet(void)
{
}

void Bullet::InitBullet()
{
	model = new PrimitiveClass();
	model->GenerateCone(0.2, 0.2, 10, RERED);
	//m_pCone->LoadModel("bullet.obj", "bullet");

	collider = new MyBoundingBoxClass(model->GetVertexList());
	collider->SetColliding(false);
}

void Bullet::Update(float globalTime)
{
	if (isFired)
	{
		ChangePosition(globalTime * velocity * forward);
		ChangeEuler(rotationSpeed);
		if (rotationSpeed.x > 0)
		{
			if (rotationSpeed.x < .15)
			{
				rotationSpeed.x = .15;
			}
			rotationSpeed.x -= .15;
		}
		if (rotationSpeed.x < 0)
		{
			if (rotationSpeed.x > -.15)
			{
				rotationSpeed.x = -.15;
			}
			rotationSpeed.x += .15;
		}
		if (rotationSpeed.y > 0)
		{
			if (rotationSpeed.y < .15)
			{
				rotationSpeed.y = .15;
			}
			rotationSpeed.y -= .15;
		}
		if (rotationSpeed.y < 0)
		{
			if (rotationSpeed.y > -.15)
			{
				rotationSpeed.y = -.15;
			}
			rotationSpeed.y += .15;
		}
		if (rotationSpeed.z > 0)
		{
			if (rotationSpeed.z < .15)
			{
				rotationSpeed.z = .15;
			}
			rotationSpeed.z -= .15;
		}
		if (rotationSpeed.z < 0)
		{
			if (rotationSpeed.z > -.15)
			{
				rotationSpeed.z = -.15;
			}
			rotationSpeed.z += .15;
		}

		bulletCam.SetPosition(position + (rotation * vector3(0.0f, 0.0f, 5.0f)) + (rotation * vector3(0.0f, 0.5f, .0f)));
		bulletCam.SetTarget(position);
		//bulletCam.SetRotation(rotation);
		bulletCam.SetUp(rotation * vector3(0, 1, 0));
	}
	UpdateWorldMatrix();

	collider->SetModelMatrix(worldMatrix);
}

void Bullet::UpdateWorldMatrix(void) 
{ 
	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}

vector3 Bullet::GetPosition(void) { return position; }
vector3 Bullet::GetForward(void) { return forward; }
vector3 Bullet::GetEuler(void) { return eulerRotation; }
quaternion Bullet::GetRotation(void) { return rotation; }
Camera Bullet::GetCamera(void) { return bulletCam; }
bool Bullet::GetFired(void) { return isFired; }
PrimitiveClass* Bullet::GetModel(void) { return model;  }
MyBoundingBoxClass* Bullet::GetCollider(void) { return collider; }
matrix4 Bullet::GetWorldMatrix(void) { return worldMatrix; }

void Bullet::SetPosition(vector3 position2) { position = position2; }
void Bullet::SetRotation(quaternion rotation2) { }
void Bullet::SetVelocity(float velocity2) {	velocity = velocity2; }
void Bullet::SetFired(bool fired) { isFired = fired; }
void Bullet::SetWorldMatrix(matrix4 mat) { worldMatrix = mat; }

void Bullet::ChangeEuler(vector3 offset)
{
	eulerRotation += offset;
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));
	forward = rotation * vector3(0, 0, -1);
}
void Bullet::ChangeRotSpeed(vector3 offset)
{
	rotationSpeed += offset;
	if (rotationSpeed.x > 2)
	{
		rotationSpeed.x = 2;
	}
	if (rotationSpeed.x < -2)
	{
		rotationSpeed.x = -2;
	}
	if (rotationSpeed.y > 2)
	{
		rotationSpeed.y = 2;
	}
	if (rotationSpeed.y < -2)
	{
		rotationSpeed.y = -2;
	}
	if (rotationSpeed.z > 2)
	{
		rotationSpeed.z = 2;
	}
	if (rotationSpeed.z < -2)
	{
		rotationSpeed.z = -2;
	}
}
void Bullet::ChangePosition(vector3 offset) { position += offset; }
void Bullet::ChangeRotation(quaternion offset) { }
void Bullet::ChangeVelocity(float offset) {	velocity += offset; }
