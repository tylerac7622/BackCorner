#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
using namespace ReEng;

class Camera {
public:

	Camera(void);

	~Camera(void);

	matrix4 GetView(void);

	matrix4 GetProjection(bool bOrthographic);

	void SetPosition(vector3 v3Position);

	void SetTarget(vector3 v3Target);

	void SetUp(vector3 v3Up);

	void MoveForward(float fIncrement);

	void MoveSideways(float fIncrement);

	void MoveVertical(float fIncrement);

	void ChangePitch(float fIncrement);

	void ChangeRoll(float fIncrement);

	void ChangeYaw(float fIncrement);
private:
	matrix4 perspectiveMatrix;
	matrix4 orthographicMatrix;
	matrix4 viewMatrix;
	matrix4 rotation;
	vector3 eye;
	vector3 center;
	vector3 up;
};

#endif 