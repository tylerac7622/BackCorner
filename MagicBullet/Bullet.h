#ifndef __BULLET_H_
#define __BULLET_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Camera.h"
#include "Object.h"

using namespace ReEng;

class Bullet : public Object{
public:

	MyBoundingBoxClass* collider;
	PrimitiveClass* model = nullptr;

	Bullet(vector3 pos, vector3 rot) ;

	~Bullet(void);

	void Reset(vector3 pos, vector3 rot) override;

	void Init(void);

	void Update(float globalTime) override;

	//gets each respective variable
	vector3 GetForward(void);
	quaternion GetRotationNoZ(void);
	quaternion GetRotationOnlyZ(void);
	Camera GetCamera(void);
	bool GetFired(void);
	//sets each respective variable
	void SetVelocity(float velocity2);
	void SetFired(bool fired);
	//add a change to each respective variable
	void ChangeEuler(vector3 offset) override;
	void ChangeRotSpeed(vector3 offset);
	void ChangeVelocity(float offset);

	void UpdateWorldMatrix(void) override;
private:

	vector3 forward;
	Camera bulletCam = Camera();
	bool isFired = false;

	float velocity = 20.0f;
	vector3 rotationSpeed;
};
#endif
