#pragma once

#include "RE\ReEngAppClass.h"
#include "MyBoundingObject.h"
using namespace ReEng;

namespace {
	class BoundingObjectManager {
	public:
		std::vector<MyBoundingObject*> objects;
		static BoundingObjectManager* GetInstance() {
			if (instance == nullptr) {
				instance = new BoundingObjectManager();
			}
			return instance;
		}
		static void ReleaseInstance() {
			if (instance != nullptr) {
				delete instance;
				instance = nullptr;
			}
		}

		void AddBox(std::vector<vector3>);
		void RenderBoxes();
		void SwitchVisiblity(MyBoundingObject*);
		void SetColor(vector3, MyBoundingObject*);
		void SetMatrix(matrix4, MyBoundingObject*);
		int GetNumBO();
		void SetVisilibty(bool, MyBoundingObject*);
		void CheckCollisons();
		void SetRotation(matrix4, MyBoundingObject*);
	private:
		static BoundingObjectManager* instance;
		BoundingObjectManager();
		bool isVisible = true;
		vector3 color = vector3(0.0f);
		
	};
	
	BoundingObjectManager* BoundingObjectManager::instance = nullptr;
}