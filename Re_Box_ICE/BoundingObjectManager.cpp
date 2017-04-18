#include "BoundingObjectManager.h"

BoundingObjectManager::BoundingObjectManager() {}


void BoundingObjectManager::AddBox(std::vector<vector3> vertixList) {
	MyBoundingObject* toPush = new MyBoundingObject(vertixList);
	objects.push_back(toPush);
}

void BoundingObjectManager::RenderBoxes() {
	for (int i = 1; i < GetNumBO(); i++) {
		objects[i]->RenderSphere();
	}
}

void BoundingObjectManager::SwitchVisiblity(MyBoundingObject* objectToSet) {
	if (isVisible) {
		objectToSet->SetVisible(false);
		return;
	}
	else if (!isVisible) {
		objectToSet->SetVisible(true);
	}
}

void BoundingObjectManager::SetColor(vector3 colorToSet, MyBoundingObject* objectToSet) {
	objectToSet->SetColor(colorToSet);
}

void BoundingObjectManager::SetVisilibty(bool toSet, MyBoundingObject* objectToSet) {
	objectToSet->SetVisible(toSet);
}

void BoundingObjectManager::SetRotation(matrix4 rotToSet, MyBoundingObject* objectToSet) {
	objectToSet->SetRotation(rotToSet);
}

void BoundingObjectManager::SetMatrix(matrix4 matrixToSet, MyBoundingObject* objectToSet) {
	objectToSet->SetRotation(matrixToSet);
}

int BoundingObjectManager::GetNumBO() {
	return objects.size();
}

void BoundingObjectManager::CheckCollisons() {
	for (int i = 1; i < objects.size() - 1; i++) {
		for (int j = i + 1; j < objects.size(); j++) {
			if (objects[i]->IsColliding(objects[j])) {
				SetColor(RERED, objects[i]);
				SetColor(RERED, objects[j]);
			}
		}
	}
}

