#include "Camera.h"

Camera::Camera(void) {
	perspectiveMatrix = glm::perspective(45.0f, 1080.0f/768.0f, 0.01f, 1000.0f);
	orthographicMatrix = glm::ortho(-15.0f, 15.0f, -15.0f, 15.0f, 0.01f, 1000.0f);
	viewMatrix = IDENTITY_M4;
	eye = vector3(0, 0, 0);
	center = vector3(0, 0, 0);
	up = vector3(0, 0, 0);
}

Camera::~Camera(void)
{
}

matrix4 Camera::GetView(void) {
	viewMatrix = rotation;
	viewMatrix *= glm::lookAt(eye, center, up);
	return viewMatrix;
}

matrix4 Camera::GetProjection(bool bOrthographic) {
	if (bOrthographic) {
		return orthographicMatrix;
	}
	return perspectiveMatrix;
}

void Camera::SetPosition(vector3 v3Position) {
	eye = v3Position;
}

void Camera::SetTarget(vector3 v3Target) {
	center = v3Target;
}

void Camera::SetUp(vector3 v3Up) {
	up = v3Up;
}

void Camera::MoveForward(float fIncrement) {
	eye.z -= fIncrement;
	center.z -= fIncrement;
}

void Camera::MoveSideways(float fIncrement) {
	eye.x += fIncrement;
	center.x += fIncrement;
}

void Camera::MoveVertical(float fIncrement) {
	eye.y += fIncrement;
	center.y += fIncrement;
}

void Camera::ChangePitch(float fIncrement) {
	
	rotation *= ToMatrix4(glm::angleAxis(fIncrement, vector3(1, 0, 0))); 
}

void Camera::ChangeRoll(float fIncrement) {
	rotation *= ToMatrix4(glm::angleAxis(fIncrement, vector3(0, 0, 1)));
}

void Camera::ChangeYaw(float fIncrement) {
	rotation *= ToMatrix4(glm::angleAxis(fIncrement, vector3(0, 1, 0)));
}