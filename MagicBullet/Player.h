#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Camera.h"
#include "MyBoundingBox.h"

using namespace ReEng;

class Player {
public:

	MyBoundingBoxClass* collider;
	PrimitiveClass* model = nullptr;

	Player(void);

	~Player(void);

	void Reset(void);

	void InitPlayer(void);

	void Update(float globalTime);

	//gets each respective variable
	vector3 GetPosition(void);
	vector3 GetForward(void);
	vector3 GetEuler(void);
	vector3 GetVelocity(void);
	quaternion GetRotation(void);
	Camera GetCamera(void);
	//sets each respective variable
	void SetPosition(vector3 position2);
	void SetRotation(quaternion rotation2);
	void SetVelocity(vector3 velocity2);
	//add a change to each respective variable
	void ChangePosition(vector3 offset);
	void ChangeEuler(vector3 offset);
	void ChangeRotation(quaternion offset);
	void ChangeVelocity(vector3 offset);

	matrix4 GetWorldMatrix(void);
	void SetWorldMatrix(matrix4 mat);
	void UpdateWorldMatrix(void);
private:

	vector3 position;
	vector3 forward;
	quaternion rotation;
	vector3 eulerRotation;
	Camera playerCam = Camera();

	vector3 velocity = vector3(0, 0, 0);

	matrix4 worldMatrix = IDENTITY_M4;
};
#endif
