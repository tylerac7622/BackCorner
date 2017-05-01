#include "Player.h"

Player::Player(void)
{
	position = vector3(0, 0, 0);
	velocity = vector3(0, 0, 0);
	eulerRotation = vector3(0.0f, 0, 0);
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));
	forward = rotation * vector3(0, 0, -1);

	playerCam.SetPosition(vector3(0.0f, 0.0f, 15.0f));
	playerCam.SetTarget(ZERO_V3);
	playerCam.SetUp(REAXISY);

	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}

void Player::Reset(void)
{
	position = vector3(0, 0, 0);
	velocity = vector3(0, 0, 0);
	eulerRotation = vector3(0.0f, 0, 0);
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));
	forward = rotation * vector3(0, 0, -1);

	playerCam.SetPosition(vector3(0.0f, 0.0f, 15.0f));
	playerCam.SetTarget(ZERO_V3);
	playerCam.SetUp(REAXISY);

	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}

Player::~Player(void)
{
}

void Player::InitPlayer(void)
{
	model = new PrimitiveClass();
	model->GenerateCube(1.0f, RERED);
	//m_pCone->LoadModel("bullet.obj", "bullet");

	collider = new MyBoundingBoxClass(model->GetVertexList());
	collider->SetColliding(false);
}

void Player::Update(float globalTime)
{
	ChangePosition(quaternion(vector3(0, PI * eulerRotation.y / 180, 0)) * velocity * globalTime);
}

void Player::UpdateWorldMatrix(void)
{
	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}

vector3 Player::GetPosition(void) { return position; }
vector3 Player::GetForward(void) { return forward; }
vector3 Player::GetEuler(void) { return eulerRotation; }
vector3 Player::GetVelocity(void) { return velocity; }
quaternion Player::GetRotation(void) { return rotation; }
Camera Player::GetCamera(void) { return playerCam; }
matrix4 Player::GetWorldMatrix(void) { return worldMatrix; }

void Player::SetPosition(vector3 position2) 
{ 
	position = position2;

	playerCam.SetPosition(position + (rotation * vector3(0.0f, 1.0f, 0.0f)) + (rotation * vector3(0.0f, 0.0f, 0.0f)));
	playerCam.SetTarget(playerCam.GetPosition() + forward);
	playerCam.SetUp(rotation * vector3(0, 1, 0));

	UpdateWorldMatrix();

	collider->SetModelMatrix(worldMatrix);
}
void Player::SetRotation(quaternion rotation2) { }
void Player::SetVelocity(vector3 velocity2) { velocity = velocity2; }
void Player::SetWorldMatrix(matrix4 mat) { worldMatrix = mat; }

void Player::ChangeEuler(vector3 offset)
{
	eulerRotation += offset;
	if (eulerRotation.x < -15)
	{
		eulerRotation.x = -15;
	}
	if (eulerRotation.x > 90)
	{
		eulerRotation.x = 90;
	}
	rotation = quaternion(vector3(PI * eulerRotation.x / 180, PI * eulerRotation.y / 180, PI * eulerRotation.z / 180));
	forward = rotation * vector3(0, 0, -1);
}
void Player::ChangePosition(vector3 offset) 
{ 
	position += offset;

	playerCam.SetPosition(position + (rotation * vector3(0.0f, 1.0f, 0.0f)) + (rotation * vector3(0.0f, 0.0f, 0.0f)));
	playerCam.SetTarget(playerCam.GetPosition() + forward);
	playerCam.SetUp(rotation * vector3(0, 1, 0));

	UpdateWorldMatrix();

	collider->SetModelMatrix(worldMatrix);
}
void Player::ChangeRotation(quaternion offset) { }
void Player::ChangeVelocity(vector3 offset) { velocity += offset; }
