#include "Bullet.h"

Bullet::Bullet(void)
{
	position = vector3(0, 2, 0);
	rotation = IDENTITY_M4;
	velocity = 20.0f;
	turningRotation = 270;
	forward = vector3(cos(PI * turningRotation / 180.0f), 0, sin(PI * turningRotation / 180.0f));

	bulletCam.SetPosition(vector3(0.0f, 0.0f, 15.0f));
	bulletCam.SetTarget(ZERO_V3);
	bulletCam.SetUp(REAXISY);

	isFired = false;
}

Bullet::~Bullet(void)
{

}

void Bullet::Update(float globalTime)
{
	if (isFired)
	{
		ChangePosition(globalTime * velocity * forward);
		bulletCam.SetPosition(position + (forward * vector3(-10.0f, 0.0f, -10.0f)) + vector3(0.0f, 1.0f, .0f));
		bulletCam.SetTarget(position);
	}
}

vector3 Bullet::GetPosition(void)
{
	return position;
}

void Bullet::ChangePosition(vector3 offset)
{
	position += offset;
}

void Bullet::SetPosition(vector3 position2)
{
	position = position2;
}

void Bullet::ChangeTurn(float offset)
{
	turningRotation += offset;
	forward = vector3(cos(PI * turningRotation/180.0f), 0, sin(PI * turningRotation / 180.0f));
}

void Bullet::ChangeRotation(matrix4 offset)
{

}

void Bullet::SetRotation(matrix4 rotation2)
{

}

vector3 Bullet::GetForward(void)
{
	return forward;
}

void Bullet::ChangeVelocity(float offset)
{
	velocity += offset;
}

void Bullet::SetVelocity(float velocity2)
{
	velocity = velocity2;
}
Camera Bullet::GetCamera(void)
{
	return bulletCam;
}
void Bullet::SetFired(bool fired)
{
	isFired = fired;
}
bool Bullet::GetFired(void)
{
	return isFired;
}