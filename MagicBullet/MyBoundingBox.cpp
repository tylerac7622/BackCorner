#include "MyBoundingBox.h"

MyBoundingBoxClass::MyBoundingBoxClass(std::vector<vector3> vertexList)
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

	reSize.x = glm::distance(vector3(m_v3MinGlobal.x, 0.0, 0.0), vector3(m_v3MaxGlobal.x, 0.0, 0.0));
	reSize.y = glm::distance(vector3(0.0, m_v3MinGlobal.y, 0.0), vector3(0.0, m_v3MaxGlobal.y, 0.0));
	reSize.z = glm::distance(vector3(0.0, 0.0, m_v3MinGlobal.z), vector3(0.0, 0.0, m_v3MaxGlobal.z));

	//m_pMeshMngr = MeshManagerSingleton::GetInstance();

	reVertexList.clear();
}

void MyBoundingBoxClass::RenderSphere()
{
	vector3 v3Color = REGREEN;
	if (true == m_bColliding)
		v3Color = RERED;

	/*m_pMeshMngr->AddSphereToRenderList(
		glm::translate(m_v3CenterGlobal) *
		glm::scale(vector3(m_fRadius) * 2.0f), v3Color, WIRE);*/

	// m_pMeshMngr->AddCubeToRenderList(glm::translate(m_v3CenterGlobal) * glm::scale(m_v3Size), v3Color, WIRE);
	m_pMeshMngr->AddCubeToRenderList(m_m4ToWorld * glm::translate(m_v3CenterLocal) * glm::scale(m_v3Size), v3Color, WIRE);
	m_pMeshMngr->AddCubeToRenderList(IDENTITY_M4 * glm::translate(m_v3CenterGlobal) * glm::scale(reSize), v3Color, WIRE);
}
void MyBoundingBoxClass::SetModelMatrix(matrix4 a_m4ToWorld)
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

	//m_pMeshMngr = MeshManagerSingleton::GetInstance();

	reVertexList.clear();

}

void MyBoundingBoxClass::SetRotation(matrix4 rot) 
{
	rotation = rot;
}

bool MyBoundingBoxClass::IsColliding(MyBoundingBoxClass* a_other)
{
	/*float fDistance = glm::distance(this->m_v3CenterGlobal, a_other->m_v3CenterGlobal);
	float fRadiiSum = this->m_fRadius + a_other->m_fRadius;
	return fDistance < fRadiiSum;*/

	
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

void MyBoundingBoxClass::SetColliding(bool input) { m_bColliding = input; }
void MyBoundingBoxClass::SetCenterLocal(vector3 input) { m_v3CenterLocal = input; }
void MyBoundingBoxClass::SetCenterGlobal(vector3 input) { m_v3CenterGlobal = input; }
void MyBoundingBoxClass::SetRadius(float input) { m_fRadius = input; }
bool MyBoundingBoxClass::GetColliding(void) { return m_bColliding; }
vector3 MyBoundingBoxClass::GetCenterLocal(void) { return m_v3CenterLocal; }
vector3 MyBoundingBoxClass::GetCenterGlobal(void) { return m_v3CenterGlobal; }
float MyBoundingBoxClass::GetRadius(void) { return m_fRadius; }
matrix4 MyBoundingBoxClass::GetModelMatrix(void) { return m_m4ToWorld; }