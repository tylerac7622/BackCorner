#ifndef __BULLET_H_
#define __BULLET_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Camera.h"
using namespace ReEng;

class Bullet {
public:

	Bullet(void);

	~Bullet(void);

	void Update(float globalTime);

	vector3 GetPosition(void);
	void ChangePosition(vector3 offset);
	void SetPosition(vector3 position2);
	void ChangeTurn(float offset);
	void ChangeRotation(matrix4 offset);
	void SetRotation(matrix4 rotation2);
	vector3 GetForward(void);
	void ChangeVelocity(float offset);
	void SetVelocity(float velocity2);
	Camera GetCamera(void);
	void SetFired(bool fired);
	bool GetFired(void);
private:

	vector3 position;
	vector3 forward;
	matrix4 rotation;
	Camera bulletCam = Camera();
	bool isFired = false;

	float velocity;
	float turningRotation = 0;
};
#endif
