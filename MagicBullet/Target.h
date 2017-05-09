#ifndef __TARGET_H_
#define __TARGET_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingBox.h"

using namespace ReEng;

class SpatialOpt;

class Target {
public:

	MyBoundingBoxClass* collider;
	PrimitiveClass* model = nullptr;
	std::vector<SpatialOpt*> currentSpec;

	Target(vector3 pos, vector3 rot);

	~Target(void);

	void Reset(vector3 pos);

	void InitTarget(vector2 size, String nam);
	void InitTarget(vector3 size, String nam);

	void Update(float globalTime);

	//gets each respective variable
	vector3 GetPosition(void);
	vector3 GetEuler(void);
	vector3 GetSize(void);
	quaternion GetRotation(void);
	String GetName(void);
	//sets each respective variable
	void SetPosition(vector3 position2);
	void SetRotation(quaternion rotation2);
	void SetEuler(vector3 euler2);
	//add a change to each respective variable
	void ChangePosition(vector3 offset);
	void ChangeEuler(vector3 offset);
	void ChangeRotation(quaternion offset);

	matrix4 GetWorldMatrix(void);
	void SetWorldMatrix(matrix4 mat);
	void UpdateWorldMatrix(void);
private:

	vector3 position;
	quaternion rotation;
	vector3 eulerRotation;
	vector3 size;
	String modelName;

	matrix4 worldMatrix = IDENTITY_M4;
};
#endif
