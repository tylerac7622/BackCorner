#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Camera.h"
#include "Object.h"

using namespace ReEng;

class Player : public Object {
public:

	Player(vector3 pos, vector3 rot);

	~Player(void);

	void Reset(vector3 pos, vector3 rot) override;

	void Update(float globalTime) override;
	void Init(void);

	//gets each respective variable
	vector3 GetForward(void);
	vector3 GetVelocity(void);
	Camera GetCamera(void);
	//sets each respective variable
	void SetPosition(vector3 position2) override;
	void SetVelocity(vector3 velocity2);
	//add a change to each respective variable
	void ChangePosition(vector3 offset) override;
	void ChangeEuler(vector3 offset) override;
	void ChangeVelocity(vector3 offset);
private:

	vector3 forward;
	Camera playerCam = Camera();

	vector3 velocity = vector3(0, 0, 0);
};
#endif
