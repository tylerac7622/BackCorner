#include "Player.h"

Player::Player(void)
{
	position = vector3(0, 0, 0);
	velocity = 20.0f;
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
	velocity = 20.0f;
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
	model->GenerateCone(1.0f, 1.0f, 10, RERED);
	//m_pCone->LoadModel("bullet.obj", "bullet");

	collider = new MyBoundingBoxClass(model->GetVertexList());
	collider->SetColliding(false);
}

void Player::Update(float globalTime)
{
	//ChangePosition(globalTime * velocity * forward);

	playerCam.SetPosition(position + (rotation * vector3(0.0f, 1.0f, 0.0f)) + (rotation * vector3(0.0f, 0.0f, 0.0f)));
	playerCam.SetTarget(playerCam.GetPosition() + forward);
	//bulletCam.SetRotation(rotation);
	playerCam.SetUp(rotation * vector3(0, 1, 0));

	UpdateWorldMatrix();

	collider->SetModelMatrix(worldMatrix);
}

void Player::UpdateWorldMatrix(void)
{
	worldMatrix = glm::translate(GetPosition());
	worldMatrix *= ToMatrix4(GetRotation());
}

vector3 Player::GetPosition(void) { return position; }
vector3 Player::GetForward(void) { return forward; }
vector3 Player::GetEuler(void) { return eulerRotation; }
quaternion Player::GetRotation(void) { return rotation; }
Camera Player::GetCamera(void) { return playerCam; }
matrix4 Player::GetWorldMatrix(void) { return worldMatrix; }

void Player::SetPosition(vector3 position2) { position = position2; }
void Player::SetRotation(quaternion rotation2) { }
void Player::SetVelocity(float velocity2) { velocity = velocity2; }
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
void Player::ChangePosition(vector3 offset) { position += offset; }
void Player::ChangeRotation(quaternion offset) { }
void Player::ChangeVelocity(float offset) { velocity += offset; }
