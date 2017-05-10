#ifndef __OBJECT_H_
#define __OBJECT_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingBox.h"

class SpatialOpt;

class Object {
public:

	PrimitiveClass* model = nullptr;
	std::vector<SpatialOpt*> currentSpec;
	MyBoundingBoxClass* collider;

	Object(vector3 pos, vector3 rot);
	Object(vector3 pos, vector3 rot, String name);
	~Object();

	virtual void Update(float globalTime);

	virtual void Reset(vector3 pos, vector3 rot);
	//gets each respective variable
	vector3 GetPosition(void);
	vector3 GetEuler(void);
	quaternion GetRotation(void);
	String GetName(void);
	//sets each respective variable
	virtual void SetPosition(vector3 position2);
	void SetRotation(quaternion rotation2);
	//add a change to each respective variable
	virtual void ChangePosition(vector3 offset);
	virtual void ChangeEuler(vector3 offset);
	void ChangeRotation(quaternion offset);

	matrix4 GetWorldMatrix(void);
	void SetWorldMatrix(matrix4 mat);
	virtual void UpdateWorldMatrix(void);

protected:
	vector3 position;
	quaternion rotation;
	vector3 eulerRotation;
	String modelName;

	matrix4 worldMatrix = IDENTITY_M4;
};
#endif
