#include "MyBoundingObject.h"

MyBoundingObject::MyBoundingObject(std::vector<vector3> vertexList)
{
	m_bColliding = false;
	m_fRadius = 0.0f;
	m_v3CenterGlobal = vector3(0.0f);

	if (vertexList.size() < 1)
		return;

	m_v3Max = vertexList[0];
	m_v3Min = vertexList[0];

	for (int i = 1; i < vertexList.size(); i++)
	{
		if (m_v3Min.x > vertexList[i].x)
		{
			m_v3Min.x = vertexList[i].x;
		}
		else if (m_v3Max.x < vertexList[i].x)
		{
			m_v3Max.x = vertexList[i].x;
		}

		if (m_v3Min.y > vertexList[i].y)
		{
			m_v3Min.y = vertexList[i].y;
		}
		else if (m_v3Max.y < vertexList[i].y)
		{
			m_v3Max.y = vertexList[i].y;
		}

		if (m_v3Min.z > vertexList[i].z)
		{
			m_v3Min.z = vertexList[i].z;
		}
		else if (m_v3Max.z < vertexList[i].z)
		{
			m_v3Max.z = vertexList[i].z;
		}
	}

	m_v3CenterLocal = m_v3CenterGlobal = (m_v3Max + m_v3Min) / 2.0f;

	m_fRadius = glm::distance(m_v3CenterGlobal, m_v3Max);

	m_v3Size.x = glm::distance(vector3(m_v3Min.x, 0.0, 0.0), vector3(m_v3Max.x, 0.0, 0.0));
	m_v3Size.y = glm::distance(vector3(0.0, m_v3Min.y, 0.0), vector3(0.0, m_v3Max.y, 0.0));
	m_v3Size.z = glm::distance(vector3(0.0, 0.0, m_v3Min.z), vector3(0.0, 0.0, m_v3Max.z));
	//--------------------------------------------------------------------------------



	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Min.x, m_v3Max.y, m_v3Max.z, 1.0f));
	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Max.x, m_v3Max.y, m_v3Max.z, 1.0f));
	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Min.x, m_v3Max.y, m_v3Min.z, 1.0f));
	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Max.x, m_v3Max.y, m_v3Min.z, 1.0f));
	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Min.x, m_v3Min.y, m_v3Max.z, 1.0f));
	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Max.x, m_v3Min.y, m_v3Max.z, 1.0f));
	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Min.x, m_v3Min.y, m_v3Min.z, 1.0f));
	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Max.x, m_v3Min.y, m_v3Min.z, 1.0f));

	m_v3MaxGlobal = vector3(reVertexList[0].x, reVertexList[0].y, reVertexList[0].z);
	m_v3MinGlobal = vector3(reVertexList[0].x, reVertexList[0].y, reVertexList[0].z);

	for (int i = 1; i < reVertexList.size(); i++)
	{
		if (m_v3MinGlobal.x > reVertexList[i].x)
		{
			m_v3MinGlobal.x = reVertexList[i].x;
		}
		else if (m_v3MaxGlobal.x < reVertexList[i].x)
		{
			m_v3MaxGlobal.x = reVertexList[i].x;
		}

		if (m_v3MinGlobal.y > reVertexList[i].y)
		{
			m_v3MinGlobal.y = reVertexList[i].y;
		}
		else if (m_v3MaxGlobal.y < reVertexList[i].y)
		{
			m_v3MaxGlobal.y = reVertexList[i].y;
		}

		if (m_v3MinGlobal.z > reVertexList[i].z)
		{
			m_v3MinGlobal.z = reVertexList[i].z;
		}
		else if (m_v3MaxGlobal.z < reVertexList[i].z)
		{
			m_v3MaxGlobal.z = reVertexList[i].z;
		}
	}

	m_v3CenterGlobal = (m_v3MaxGlobal + m_v3MinGlobal) / 2.0f;

	m_fRadius = glm::distance(m_v3CenterGlobal, m_v3Max);

	reSize.x = glm::distance(vector3(m_v3MinGlobal.x, 0.0, 0.0), vector3(m_v3MaxGlobal.x, 0.0, 0.0));
	reSize.y = glm::distance(vector3(0.0, m_v3MinGlobal.y, 0.0), vector3(0.0, m_v3MaxGlobal.y, 0.0));
	reSize.z = glm::distance(vector3(0.0, 0.0, m_v3MinGlobal.z), vector3(0.0, 0.0, m_v3MaxGlobal.z));

	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	reVertexList.clear();
}

void MyBoundingObject::RenderSphere()
{
	if (isVisible)
	{
		if (isSphereVisible)
		{
			m_pMeshMngr->AddSphereToRenderList(glm::translate(m_v3CenterGlobal) * glm::scale(vector3(m_fRadius) * 2.0f), v3Color, WIRE);
		}
		if (isBoxVisible)
		{
			m_pMeshMngr->AddCubeToRenderList(m_m4ToWorld * glm::translate(m_v3CenterLocal) * glm::scale(m_v3Size), v3Color, WIRE);
			m_pMeshMngr->AddCubeToRenderList(IDENTITY_M4 * glm::translate(m_v3CenterGlobal) * glm::scale(reSize), v3Color, WIRE);
		}
	}
}
void MyBoundingObject::SetModelMatrix(matrix4 a_m4ToWorld)
{
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	m_v3CenterGlobal = vector3(m_m4ToWorld * vector4(m_v3CenterLocal, 1.0f));
	m_v3MaxGlobal = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));
	m_v3MinGlobal = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));

	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Min.x, m_v3Max.y, m_v3Max.z, 1.0f));
	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Max.x, m_v3Max.y, m_v3Max.z, 1.0f));
	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Min.x, m_v3Max.y, m_v3Min.z, 1.0f));
	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Max.x, m_v3Max.y, m_v3Min.z, 1.0f));
	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Min.x, m_v3Min.y, m_v3Max.z, 1.0f));
	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Max.x, m_v3Min.y, m_v3Max.z, 1.0f));
	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Min.x, m_v3Min.y, m_v3Min.z, 1.0f));
	reVertexList.push_back(m_m4ToWorld * vector4(m_v3Max.x, m_v3Min.y, m_v3Min.z, 1.0f));

	m_v3MaxGlobal = vector3(reVertexList[0].x, reVertexList[0].y, reVertexList[0].z);
	m_v3MinGlobal = vector3(reVertexList[0].x, reVertexList[0].y, reVertexList[0].z);

	for (int i = 1; i < reVertexList.size(); i++)
	{
		if (m_v3MinGlobal.x > reVertexList[i].x)
		{
			m_v3MinGlobal.x = reVertexList[i].x;
		}
		else if (m_v3MaxGlobal.x < reVertexList[i].x)
		{
			m_v3MaxGlobal.x = reVertexList[i].x;
		}

		if (m_v3MinGlobal.y > reVertexList[i].y)
		{
			m_v3MinGlobal.y = reVertexList[i].y;
		}
		else if (m_v3MaxGlobal.y < reVertexList[i].y)
		{
			m_v3MaxGlobal.y = reVertexList[i].y;
		}

		if (m_v3MinGlobal.z > reVertexList[i].z)
		{
			m_v3MinGlobal.z = reVertexList[i].z;
		}
		else if (m_v3MaxGlobal.z < reVertexList[i].z)
		{
			m_v3MaxGlobal.z = reVertexList[i].z;
		}
	}

	m_v3CenterGlobal = (m_v3MaxGlobal + m_v3MinGlobal) / 2.0f;

	reSize.x = glm::distance(vector3(m_v3MinGlobal.x, 0.0, 0.0), vector3(m_v3MaxGlobal.x, 0.0, 0.0));
	reSize.y = glm::distance(vector3(0.0, m_v3MinGlobal.y, 0.0), vector3(0.0, m_v3MaxGlobal.y, 0.0));
	reSize.z = glm::distance(vector3(0.0, 0.0, m_v3MinGlobal.z), vector3(0.0, 0.0, m_v3MaxGlobal.z));

	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	reVertexList.clear();

}

void MyBoundingObject::SetRotation(matrix4 rot)
{
	rotation = rot;
}

bool MyBoundingObject::IsColliding(MyBoundingObject* a_other)
{
	/*float fDistance = glm::distance(this->m_v3CenterGlobal, a_other->m_v3CenterGlobal);
	float fRadiiSum = this->m_fRadius + a_other->m_fRadius;
	return fDistance < fRadiiSum;*/

	float fDistance = glm::distance(this->m_v3CenterGlobal, a_other->m_v3CenterGlobal);
	float fRadiiSum = this->m_fRadius + a_other->m_fRadius;
	if (fDistance < fRadiiSum)
	{

		if (this->m_v3MaxGlobal.x < a_other->m_v3MinGlobal.x)
			return false;
		else if (this->m_v3MinGlobal.x > a_other->m_v3MaxGlobal.x)
			return false;

		if (this->m_v3MaxGlobal.y < a_other->m_v3MinGlobal.y)
			return false;
		else if (this->m_v3MinGlobal.y > a_other->m_v3MaxGlobal.y)
			return false;

		if (this->m_v3MaxGlobal.z < a_other->m_v3MinGlobal.z)
			return false;
		else if (this->m_v3MinGlobal.z > a_other->m_v3MaxGlobal.z)
			return false;

		return true;
	}
	else
	{
		return false;
	}
}

void MyBoundingObject::SetColliding(bool input) { m_bColliding = input; }
void MyBoundingObject::SetCenterLocal(vector3 input) { m_v3CenterLocal = input; }
void MyBoundingObject::SetCenterGlobal(vector3 input) { m_v3CenterGlobal = input; }
void MyBoundingObject::SetRadius(float input) { m_fRadius = input; }
bool MyBoundingObject::GetColliding(void) { return m_bColliding; }
vector3 MyBoundingObject::GetCenterLocal(void) { return m_v3CenterLocal; }
vector3 MyBoundingObject::GetCenterGlobal(void) { return m_v3CenterGlobal; }
float MyBoundingObject::GetRadius(void) { return m_fRadius; }
matrix4 MyBoundingObject::GetModelMatrix(void) { return m_m4ToWorld; }
vector3 MyBoundingObject::GetMax(void) { return m_v3MaxGlobal; }
vector3 MyBoundingObject::GetMin(void) { return m_v3MinGlobal; }
void MyBoundingObject::SetColor(vector3 color) { v3Color = color; }
bool MyBoundingObject::GetVisible(void) { return isVisible; }
void MyBoundingObject::SetVisible(bool vis) { isVisible = vis; }
bool MyBoundingObject::GetSphereVisible(void) { return isSphereVisible; }
void MyBoundingObject::SetSphereVisible(bool vis) { isSphereVisible = vis; }
bool MyBoundingObject::GetBoxVisible(void) { return isBoxVisible; }
void MyBoundingObject::SetBoxVisible(bool vis) { isBoxVisible = vis; }