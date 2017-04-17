#include "Bullet.h"

Bullet::Bullet(void)
{
	position = vector3(0, 2, 0);
	rotation = IDENTITY_M4;
	velocity = .4f;
	turningRotation = 270;
	forward = vector3(cos(PI * turningRotation / 180.0f), 0, sin(PI * turningRotation / 180.0f));
}

Bullet::~Bullet(void)
{

}

void Bullet::Update(void)
{
	ChangePosition(velocity * forward);
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