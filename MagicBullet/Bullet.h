#ifndef __BULLET_H_
#define __BULLET_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Camera.h"
#include "MyBoundingBox.h"
using namespace ReEng;

class Bullet {
public:

	Bullet(void);

	~Bullet(void);

	void Update(float globalTime);

	//gets each respective variable
	vector3 GetPosition(void);
	vector3 GetForward(void);
	Camera GetCamera(void);
	bool GetFired(void);
	//sets each respective variable
	void SetPosition(vector3 position2);
	void SetRotation(matrix4 rotation2);
	void SetVelocity(float velocity2);
	void SetFired(bool fired);
	//add a change to each respective variable
	void ChangePosition(vector3 offset);
	void ChangeTurn(float offset);
	void ChangeRotation(matrix4 offset);
	void ChangeVelocity(float offset);
private:

	vector3 position;
	vector3 forward;
	matrix4 rotation;
	Camera bulletCam = Camera();
	bool isFired = false;

	float velocity = 20.0f;
	float turningRotation = 0;
};
#endif
