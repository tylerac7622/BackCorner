#ifndef __TARGET_H_
#define __TARGET_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Object.h"

using namespace ReEng;

class Target : public Object {
public:

	Target(vector3 pos, vector3 rot);

	~Target(void);

	void Update(float globalTime) override;

	bool IsActive(void);

	void SetActive(bool act);
private:
	bool active;
};
#endif
