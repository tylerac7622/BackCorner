#include "Bullet.h"

Bullet::Bullet(void)
{
	position = vector3(0, 0, 0);
	forward = vector3(0, 0, 0);
	rotation = IDENTITY_M4;
	velocity = 15;
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

void Bullet::ChangeRotation(matrix4 offset)
{

}

void Bullet::SetRotation(matrix4 rotation2)
{

}

void Bullet::ChangeVelocity(float offset)
{
	velocity += offset;
}

void Bullet::SetVelocity(float velocity2)
{
	velocity = velocity2l
}