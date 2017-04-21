#include "Bullet.h"

Bullet::Bullet(void)
{
	position = vector3(0, 2, 0);
	velocity = 20.0f;
	turningRotation = 270;
	turningRotationY = 0;
	eulerRotation = vector3(0, 0, 0);
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));
	forward = rotation * vector3(0, 0, -1);

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

		bulletCam.SetPosition(position + (rotation * vector3(0.0f, 0.0f, 10.0f)) + (rotation * vector3(0.0f, 1.0f, .0f)));
		bulletCam.SetTarget(position);
		//bulletCam.SetRotation(rotation);
		bulletCam.SetUp(rotation * vector3(0, 1, 0));
	}
}

vector3 Bullet::GetPosition(void) { return position; }
vector3 Bullet::GetForward(void) { return forward; }
vector3 Bullet::GetEuler(void) { return eulerRotation; }
quaternion Bullet::GetRotation(void) { return rotation; }
Camera Bullet::GetCamera(void) { return bulletCam; }
bool Bullet::GetFired(void) { return isFired; }

void Bullet::SetPosition(vector3 position2) { position = position2; }
void Bullet::SetRotation(quaternion rotation2) { }
void Bullet::SetVelocity(float velocity2) {	velocity = velocity2; }
void Bullet::SetFired(bool fired) { isFired = fired; }

void Bullet::ChangeEuler(vector3 offset)
{
	eulerRotation += offset;
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));
	forward = rotation * vector3(0, 0, -1);
}
void Bullet::ChangePosition(vector3 offset) { position += offset; }
void Bullet::ChangeRotation(quaternion offset) { }
void Bullet::ChangeVelocity(float offset) {	velocity += offset; }
