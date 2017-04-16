#ifndef __BULLET_H_
#define __BULLET_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
using namespace ReEng;

class Bullet {
public:

	Bullet(void);

	~Bullet(void);

	void Update(void);

	vector3 GetPosition(void);

	void ChangePosition(vector3 offset);

	void SetPosition(vector3 position2);

	void ChangeRotation(matrix4 offset);

	void SetRotation(matrix4 rotation2);

	void ChangeVelocity(float offset);

	void SetVelocity(float velocity2);
private:

	vector3 position;
	vector3 forward;
	matrix4 rotation;

	float velocity;
};
#endif
