#include "Bullet.h"

Bullet::Bullet(vector3 pos, vector3 rot) : Object(pos, rot)
{
	velocity = 20.0f;
	forward = rotation * vector3(0, 0, -1);
	rotationSpeed = vector3(0, 0, 1);

	bulletCam.SetPosition(vector3(0.0f, 0.0f, 15.0f));
	bulletCam.SetTarget(ZERO_V3);
	bulletCam.SetUp(REAXISY);

	isFired = false;
}

void Bullet::Reset(vector3 pos, vector3 rot)
{
	Object::Reset(pos, rot);
	velocity = 20.0f;
	forward = rotation * vector3(0, 0, -1);
	rotationSpeed = vector3(0, 0, 1);

	bulletCam.SetPosition(vector3(0.0f, 0.0f, 15.0f));
	bulletCam.SetTarget(ZERO_V3);
	bulletCam.SetUp(REAXISY);

	isFired = false;
}

Bullet::~Bullet(void)
{
}

void Bullet::Init(void)
{
	modelName = "bullet";
}

void Bullet::Update(float globalTime)
{
	if (isFired)
	{
		ChangePosition(globalTime * velocity * forward);
		ChangeEuler(rotationSpeed);

		quaternion adjustedRotation = quaternion(vector3(PI * (eulerRotation.x + (2 * rotationSpeed.x)) / 180, PI * (eulerRotation.y + (2 * rotationSpeed.y)) / 180, 0));

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

		bulletCam.SetPosition(position + (adjustedRotation * vector3(0.0f, 0.0f, 10.0f)) + (adjustedRotation * vector3(0.0f, 1.5f, .0f)));
		bulletCam.SetTarget(position);
		//bulletCam.SetRotation(rotation);
		bulletCam.SetUp(adjustedRotation * vector3(0, 1, 0));

	}
	UpdateWorldMatrix();

	collider->SetModelMatrix(worldMatrix);

	currentSpec.clear();
}

void Bullet::UpdateWorldMatrix(void) 
{ 
	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotationNoZ());
	worldMatrix *= ToMatrix4(GetRotationOnlyZ());
	//worldMatrix *= glm::scale(vector3(.4, .4, .4));
}

vector3 Bullet::GetForward(void) { return forward; }
quaternion Bullet::GetRotationNoZ(void) { return quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * 0 / 180)); }
quaternion Bullet::GetRotationOnlyZ(void) { return quaternion(vector3(PI * 0 / 180, PI * 0 / 180, PI * eulerRotation.z / 180)); }
Camera Bullet::GetCamera(void) { return bulletCam; }
bool Bullet::GetFired(void) { return isFired; }

void Bullet::SetVelocity(float velocity2) {	velocity = velocity2; }
void Bullet::SetFired(bool fired) { isFired = fired; }
void Bullet::ChangeEuler(vector3 offset)
{
	eulerRotation += offset;
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * 0 / 180));
	forward = rotation * vector3(0, 0, -1);
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));
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
}
void Bullet::ChangeVelocity(float offset) {	velocity += offset; }
