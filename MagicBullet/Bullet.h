#ifndef __BULLET_H_
#define __BULLET_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Camera.h"
#include "MyBoundingBox.h"
using namespace ReEng;

class Bullet {
public:

	MyBoundingBoxClass* collider;
	PrimitiveClass* model = nullptr;

	Bullet(vector3 pos, vector3 rot);

	~Bullet(void);

	void Reset(vector3 pos, vector3 rot);

	void InitBullet();

	void Update(float globalTime);

	//gets each respective variable
	vector3 GetPosition(void);
	vector3 GetForward(void);
	vector3 GetEuler(void);
	quaternion GetRotation(void);
	Camera GetCamera(void);
	bool GetFired(void);
	//sets each respective variable
	void SetPosition(vector3 position2);
	void SetRotation(quaternion rotation2);
	void SetVelocity(float velocity2);
	void SetFired(bool fired);
	//add a change to each respective variable
	void ChangePosition(vector3 offset);
	void ChangeEuler(vector3 offset);
	void ChangeRotSpeed(vector3 offset);
	void ChangeRotation(quaternion offset);
	void ChangeVelocity(float offset);

	PrimitiveClass* GetModel(void);
	MyBoundingBoxClass* GetCollider(void);
	matrix4 GetWorldMatrix(void);
	void SetWorldMatrix(matrix4 mat);
	void UpdateWorldMatrix(void);
private:

	vector3 position;
	vector3 forward;
	quaternion rotation;
	vector3 eulerRotation;
	Camera bulletCam = Camera();
	bool isFired = false;

	float velocity = 20.0f;
	vector3 rotationSpeed;

	matrix4 worldMatrix = IDENTITY_M4;
};
#endif
