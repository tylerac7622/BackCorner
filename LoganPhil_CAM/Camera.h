#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#endif //_MAIN_H

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
//#include <chrono>

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll
namespace {
	class Camera {
	public:
		static Camera* GetInstance() {
			if (instance == nullptr) {
				instance = new Camera();
			}
			return instance;
		}
		static void ReleaseInstance() {
			if (instance != nullptr) {
				delete instance;
				instance = nullptr;
			}
		}
		Camera() {
			perspective = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
			camLocation = IDENTITY_M4;
			v3_Eye = glm::vec3(0.0f, 0.0f, 15.0f); //default eye position 15 units on the Z axis  
			v3_Target = glm::vec3(0.0f, 0.0f, 0.0f);
			v3_Up = glm::vec3(0.0f, 1.0f, 0.0f); //default up in the Y direction
			locationX = 0.0f;
			locationY = 0.0f;
			locationZ = 0.0f;
			orthoPerspective = glm::ortho(-10.0f, 10.0f, -5.0f, 5.0f, 0.01f, 1000.0f);
		};

		~Camera() {};

		matrix4 GetView(void) {
			return getRotation() * camLocation * glm::lookAt(v3_Eye, v3_Target, v3_Up);
		};

		matrix4 getProjection(bool bOrthographic) {
			if (!bOrthographic) {
				return perspective;
			}
			else
				return orthoPerspective;
		};

		matrix4 getRotation() {
			quaternion rot = quaternion(vector3(xAngle, yAngle, zAngle));
			return ToMatrix4(rot);
		}

		void ChangePitch(float fIncrement) {
		    xAngle += fIncrement;
			RotationX = glm::angleAxis(xAngle, vector3(1.0f, 0.0f, 0.0f));
		};

		void ChangeRoll(float fIncrement) {
			zAngle += fIncrement;
			RotationZ = glm::angleAxis(zAngle, vector3(0.0f, 0.0f, 1.0f));
		}

		void ChangeYaw(float fIncrement) {
			yAngle += fIncrement;
			RotationY = glm::angleAxis(yAngle, vector3(0.0f, 1.0f, 0.0f));
		}

		void SetPosition(vector3 v3Position) {
			camLocation = glm::translate(v3Position);
		};

		void PASSED(vector3 v3Target) {
			//return out if the target is behind our eye
			if (v3_Target.x < v3Target.x) { return; }
			else if (v3_Target.y < v3Target.y) { return; }
			else if (v3_Target.z < v3Target.z) { return; }

			v3_Target = v3Target;
		};

		void SetUp(vector3 v3Up) {
			v3_Up = v3Up;
		};

		//NOTE I'm not sure that we have to change the eye and target vectors when moving the camera.  This only really changes the line of site, not the location in space

		void MoveForward(float fIncrement) {
		//	v3_Eye.z += fIncrement;
			//v3_Target.z += fIncrement;
		//	camLocation += glm::translate(vector3(0.0f, 0.0f, fIncrement));
			locationZ += fIncrement;
			camLocation = glm::translate(vector3(locationX, locationY, locationZ));
		};

		void MoveSideways(float fIncrement) {
			//v3_Eye.x += fIncrement;
			//v3_Target.x += fIncrement;
		//	camLocation += glm::translate(vector3(fIncrement, 0.0f, 0.0f));
			locationX += fIncrement;
			camLocation = glm::translate(vector3(locationX, locationY, locationZ));
		};

		void MoveVertical(float fIncrement) {
			//v3_Eye.y += fIncrement;
		//	v3_Target.y += fIncrement;
			//camLocation += glm::translate(vector3(0.0f, fIncrement, 0.0f));
			locationY += fIncrement;
			camLocation = glm::translate(vector3(locationX, locationY, locationZ));
		};

	private:
		matrix4 perspective;
		matrix4 camLocation;
		matrix4 orthoPerspective;
		float locationX;
		float locationY;
		float locationZ;
		float xAngle = 0.0f;
		float yAngle = 0.0f;
		float zAngle = 0.0f;

		quaternion RotationX = glm::angleAxis(xAngle, vector3(1.0f, 0.0f, 0.0f));
		quaternion RotationY = glm::angleAxis(yAngle, vector3(0.0f, 1.0f, 0.0f));
		quaternion RotationZ = glm::angleAxis(zAngle, vector3(0.0f, 0.0f, 1.0f));

		vector3 v3_Up;
		vector3 v3_Target;
		vector3 v3_Eye;
		//for example          EYE(forward)                  TARGET                        UP
		//glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 14.0f), glm::vec3(0.0f, 1.0f, 0.0f)

		static Camera* instance;

	};
	Camera* Camera::instance = nullptr;
}