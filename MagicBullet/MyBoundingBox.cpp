#include "MyBoundingBox.h"

MyBoundingBoxClass::MyBoundingBoxClass(std::vector<vector3> vertexList, float scale)
{
	m_m4ToWorld = IDENTITY_M4;

	m_v3CenterLocal = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_v3CenterGlobal = vector3(0.0f);
	m_v3MinGlobal = vector3(0.0f);
	m_v3MaxGlobal = vector3(0.0f);

	m_v3HalfWidthGlobal = vector3(0.0f);

	m_fRadius = 0.0f;

	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	//reVertexList = vertexList;

	//Count the points of the incoming list
	//Count the points of the incoming list
	uint nVertexCount = vertexList.size();

	//If there are none just return, we have no information to create the BS from
	if (nVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3Max = m_v3Min = vertexList[0];

	//Get the max and min out of the list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		if (m_v3Min.x > vertexList[nVertex].x) //If min is larger than current
			m_v3Min.x = vertexList[nVertex].x;
		else if (m_v3Max.x < vertexList[nVertex].x)//if max is smaller than current
			m_v3Max.x = vertexList[nVertex].x;

		if (m_v3Min.y > vertexList[nVertex].y) //If min is larger than current
			m_v3Min.y = vertexList[nVertex].y;
		else if (m_v3Max.y < vertexList[nVertex].y)//if max is smaller than current
			m_v3Max.y = vertexList[nVertex].y;

		if (m_v3Min.z > vertexList[nVertex].z) //If min is larger than current
			m_v3Min.z = vertexList[nVertex].z;
		else if (m_v3Max.z < vertexList[nVertex].z)//if max is smaller than current
			m_v3Max.z = vertexList[nVertex].z;
	}

	//with the max and the min we calculate the center
	m_v3CenterLocal = (m_v3Min + m_v3Max) / 2.0f;

	m_fRadius = glm::distance(m_v3CenterLocal, m_v3Max);
	//another way of doing this, except that with it the sphere just surrounds the object making the
	//pretest kind of useless
	//m_fRadius = 0;
	//for (uint nVertex = 0; nVertex < nVertexCount; nVertex++)
	//{
	//	float fDistance = glm::distance(m_v3Center, a_lVectorList[nVertex]);
	//	if (m_fRadius < fDistance)
	//		m_fRadius = fDistance;
	//}

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidthLocal = (m_v3Max - m_v3Min) / 2.0f;

	m_v3HalfWidthLocal *= scale;
	m_v3Max = m_v3CenterLocal + m_v3HalfWidthLocal;
	m_v3Min = m_v3CenterLocal - m_v3HalfWidthLocal;

	m_v3MaxGlobal = m_v3Max;
	m_v3MinGlobal = m_v3Min;
	m_v3CenterGlobal = m_v3CenterLocal;
	m_v3HalfWidthGlobal = m_v3HalfWidthLocal;
}

void MyBoundingBoxClass::RenderSphere()
{
	/*vector3 v3Color = REGREEN;
	if (true == m_bColliding)
	v3Color = RERED;

	// m_pMeshMngr->AddCubeToRenderList(glm::translate(m_v3CenterGlobal) * glm::scale(m_v3Size), v3Color, WIRE);
	m_pMeshMngr->AddCubeToRenderList(m_m4ToWorld * glm::translate(m_v3CenterLocal) * glm::scale(m_v3Size), v3Color, WIRE);
	m_pMeshMngr->AddCubeToRenderList(IDENTITY_M4 * glm::translate(m_v3CenterGlobal) * glm::scale(reSize), v3Color, WIRE);*/
	m_pMeshMngr->AddCubeToRenderList(glm::translate(IDENTITY_M4, m_v3CenterGlobal) *
		glm::scale(m_v3HalfWidthGlobal * 2.0f), RERED, WIRE);
}
void MyBoundingBoxClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	//If there are no changes in the Model Matrix there is no need
	//of doing further calculations
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	//Calculate the vertex that makes the Object
	vector3 v3Corner[8];
	v3Corner[0] = vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z);
	v3Corner[1] = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	v3Corner[2] = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	v3Corner[3] = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);

	v3Corner[4] = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	v3Corner[5] = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	v3Corner[6] = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	v3Corner[7] = vector3(m_v3Max.x, m_v3Max.y, m_v3Max.z);
	//Get vectors in global space
	for (uint nVertex = 0; nVertex < 8; nVertex++)
	{
		v3Corner[nVertex] = vector3(m_m4ToWorld * vector4(v3Corner[nVertex], 1.0f));
	}

	//Get the max and min out of the list
	m_v3MaxGlobal = m_v3MinGlobal = v3Corner[0];
	for (uint nVertex = 1; nVertex < 8; nVertex++)
	{
		if (m_v3MinGlobal.x > v3Corner[nVertex].x) //If min is larger than current
			m_v3MinGlobal.x = v3Corner[nVertex].x;
		else if (m_v3MaxGlobal.x < v3Corner[nVertex].x)//if max is smaller than current
			m_v3MaxGlobal.x = v3Corner[nVertex].x;

		if (m_v3MinGlobal.y > v3Corner[nVertex].y) //If min is larger than current
			m_v3MinGlobal.y = v3Corner[nVertex].y;
		else if (m_v3MaxGlobal.y < v3Corner[nVertex].y)//if max is smaller than current
			m_v3MaxGlobal.y = v3Corner[nVertex].y;

		if (m_v3MinGlobal.z > v3Corner[nVertex].z) //If min is larger than current
			m_v3MinGlobal.z = v3Corner[nVertex].z;
		else if (m_v3MaxGlobal.z < v3Corner[nVertex].z)//if max is smaller than current
			m_v3MaxGlobal.z = v3Corner[nVertex].z;
	}
	m_v3CenterGlobal = (m_v3MinGlobal + m_v3MaxGlobal) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidthGlobal = (m_v3MaxGlobal - m_v3MinGlobal) / 2.0f;

	m_fRadius = glm::distance(m_v3CenterGlobal, m_v3MaxGlobal);
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


	/*if (this->m_v3MaxGloballobal.x < a_other->m_v3MinGloballobal.x)
	return false;
	else if (this->m_v3MinGloballobal.x > a_other->m_v3MaxGloballobal.x)
	return false;

	if (this->m_v3MaxGloballobal.y < a_other->m_v3MinGloballobal.y)
	return false;
	else if (this->m_v3MinGloballobal.y > a_other->m_v3MaxGloballobal.y)
	return false;

	if (this->m_v3MaxGloballobal.z < a_other->m_v3MinGloballobal.z)
	return false;
	else if (this->m_v3MinGloballobal.z > a_other->m_v3MaxGloballobal.z)
	return false;

	return true;*/

	return SAT(a_other);
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
bool MyBoundingBoxClass::SAT(MyBoundingBoxClass* const a_pOther)
{
	// Get the information of this object
	vector3 v3CenterGlobalA = GetCenterGlobal();
	matrix4 mToWorldA = GetModelMatrix();
	vector3 v3RotationA[3];
	v3RotationA[0] = vector3(mToWorldA[0][0], mToWorldA[0][1], mToWorldA[0][2]);
	v3RotationA[1] = vector3(mToWorldA[1][0], mToWorldA[1][1], mToWorldA[1][2]);
	v3RotationA[2] = vector3(mToWorldA[2][0], mToWorldA[2][1], mToWorldA[2][2]);

	//Get the information of the other object
	vector3 v3CenterGlobalB = a_pOther->GetCenterGlobal();
	matrix4 mToWorldB = a_pOther->GetModelMatrix();
	vector3 v3RotationB[3];
	v3RotationB[0] = vector3(mToWorldB[0][0], mToWorldB[0][1], mToWorldB[0][2]);
	v3RotationB[1] = vector3(mToWorldB[1][0], mToWorldB[1][1], mToWorldB[1][2]);
	v3RotationB[2] = vector3(mToWorldB[2][0], mToWorldB[2][1], mToWorldB[2][2]);

	float fCenterAToMiddle, fCenterBToMiddle;
	glm::mat3 m3Rotation, m3RotationAbs;

	// Compute rotation matrix expressing b in a's coordinate frame
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m3Rotation[i][j] = glm::dot(v3RotationA[i], v3RotationB[j]);

	// Compute translation vector v3Distance (this is the distance between both centers)
	vector3 v3Distance = v3CenterGlobalB - v3CenterGlobalA; //distance in global space
															// Bring translation into a's coordinate frame
	v3Distance = vector3(glm::dot(v3Distance, v3RotationA[0]), glm::dot(v3Distance, v3RotationA[1]), glm::dot(v3Distance, v3RotationA[2])); //distance in A's local
																																			// their cross product is (near) null (see the orange book for details)
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m3RotationAbs[i][j] = std::abs(m3Rotation[i][j]) + 0.0001f;

	// Test axes L = AX <- 0
	fCenterAToMiddle = m_v3HalfWidthLocal.x;
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.x * m3RotationAbs[0][0] + a_pOther->m_v3HalfWidthLocal.y * m3RotationAbs[0][1] + a_pOther->m_v3HalfWidthLocal.z * m3RotationAbs[0][2];
	if (std::abs(v3Distance.x) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axes L = AY <- 1
	fCenterAToMiddle = m_v3HalfWidthLocal.y;
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.x * m3RotationAbs[1][0] + a_pOther->m_v3HalfWidthLocal.y * m3RotationAbs[1][1] + a_pOther->m_v3HalfWidthLocal.z * m3RotationAbs[1][2];
	if (std::abs(v3Distance.y) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axes L = AZ <- 2
	fCenterAToMiddle = m_v3HalfWidthLocal.z;
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.x * m3RotationAbs[2][0] + a_pOther->m_v3HalfWidthLocal.y * m3RotationAbs[2][1] + a_pOther->m_v3HalfWidthLocal.z * m3RotationAbs[2][2];
	if (std::abs(v3Distance.z) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axes L = BX <- 3
	fCenterAToMiddle = m_v3HalfWidthLocal.x * m3RotationAbs[0][0] + m_v3HalfWidthLocal.y * m3RotationAbs[1][0] + m_v3HalfWidthLocal.z * m3RotationAbs[2][0];
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.x;
	if (std::abs(v3Distance.x * m3Rotation[0][0] + v3Distance.y * m3Rotation[1][0] + v3Distance.z * m3Rotation[2][0]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axes L = BY <- 4
	fCenterAToMiddle = m_v3HalfWidthLocal.x * m3RotationAbs[0][1] + m_v3HalfWidthLocal.y * m3RotationAbs[1][1] + m_v3HalfWidthLocal.z * m3RotationAbs[2][1];
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.y;
	if (std::abs(v3Distance.x * m3Rotation[0][1] + v3Distance.y * m3Rotation[1][1] + v3Distance.z * m3Rotation[2][1]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axes L = BZ <- 5
	fCenterAToMiddle = m_v3HalfWidthLocal.x * m3RotationAbs[0][2] + m_v3HalfWidthLocal.y * m3RotationAbs[1][2] + m_v3HalfWidthLocal.z * m3RotationAbs[2][2];
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.z;
	if (std::abs(v3Distance.x * m3Rotation[0][2] + v3Distance.y * m3Rotation[1][2] + v3Distance.z * m3Rotation[2][2]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AX x BX <- 6
	fCenterAToMiddle = m_v3HalfWidthLocal.y * m3RotationAbs[2][0] + m_v3HalfWidthLocal.z * m3RotationAbs[1][0];
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.y * m3RotationAbs[0][2] + a_pOther->m_v3HalfWidthLocal.z * m3RotationAbs[0][1];
	if (std::abs(v3Distance.z * m3Rotation[1][0] - v3Distance.y * m3Rotation[2][0]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AX x BY <- 7
	fCenterAToMiddle = m_v3HalfWidthLocal.y * m3RotationAbs[2][1] + m_v3HalfWidthLocal.z * m3RotationAbs[1][1];
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.x * m3RotationAbs[0][2] + a_pOther->m_v3HalfWidthLocal.z * m3RotationAbs[0][0];
	if (std::abs(v3Distance.z * m3Rotation[1][1] - v3Distance.y * m3Rotation[2][1]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AX x BZ <- 8
	fCenterAToMiddle = m_v3HalfWidthLocal.y * m3RotationAbs[2][2] + m_v3HalfWidthLocal.z * m3RotationAbs[1][2];
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.x * m3RotationAbs[0][1] + a_pOther->m_v3HalfWidthLocal.y * m3RotationAbs[0][0];
	if (std::abs(v3Distance.z * m3Rotation[1][2] - v3Distance.y * m3Rotation[2][2]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AY x BX <- 9
	fCenterAToMiddle = m_v3HalfWidthLocal.x * m3RotationAbs[2][0] + m_v3HalfWidthLocal.z * m3RotationAbs[0][0];
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.y * m3RotationAbs[1][2] + a_pOther->m_v3HalfWidthLocal.z * m3RotationAbs[1][1];
	if (std::abs(v3Distance.x * m3Rotation[2][0] - v3Distance.z * m3Rotation[0][0]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AY x BY <- 10
	fCenterAToMiddle = m_v3HalfWidthLocal.x * m3RotationAbs[2][1] + m_v3HalfWidthLocal.z * m3RotationAbs[0][1];
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.x * m3RotationAbs[1][2] + a_pOther->m_v3HalfWidthLocal.z * m3RotationAbs[1][0];
	if (std::abs(v3Distance.x * m3Rotation[2][1] - v3Distance.z * m3Rotation[0][1]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AY x BZ <- 11
	fCenterAToMiddle = m_v3HalfWidthLocal.x * m3RotationAbs[2][2] + m_v3HalfWidthLocal.z * m3RotationAbs[0][2];
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.x * m3RotationAbs[1][1] + a_pOther->m_v3HalfWidthLocal.y * m3RotationAbs[1][0];
	if (std::abs(v3Distance.x * m3Rotation[2][2] - v3Distance.z * m3Rotation[0][2]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AZ x BX <- 12
	fCenterAToMiddle = m_v3HalfWidthLocal.x * m3RotationAbs[1][0] + m_v3HalfWidthLocal.y * m3RotationAbs[0][0];
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.y * m3RotationAbs[2][2] + a_pOther->m_v3HalfWidthLocal.z * m3RotationAbs[2][1];
	if (std::abs(v3Distance.y * m3Rotation[0][0] - v3Distance.x * m3Rotation[1][0]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AZ x BY <- 13
	fCenterAToMiddle = m_v3HalfWidthLocal.x * m3RotationAbs[1][1] + m_v3HalfWidthLocal.y * m3RotationAbs[0][1];
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.x * m3RotationAbs[2][2] + a_pOther->m_v3HalfWidthLocal.z * m3RotationAbs[2][0];
	if (std::abs(v3Distance.y * m3Rotation[0][1] - v3Distance.x * m3Rotation[1][1]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AZ x BZ <- 14
	fCenterAToMiddle = m_v3HalfWidthLocal.x * m3RotationAbs[1][2] + m_v3HalfWidthLocal.y * m3RotationAbs[0][2];
	fCenterBToMiddle = a_pOther->m_v3HalfWidthLocal.x * m3RotationAbs[2][1] + a_pOther->m_v3HalfWidthLocal.y * m3RotationAbs[2][0];
	if (std::abs(v3Distance.y * m3Rotation[0][2] - v3Distance.x * m3Rotation[1][2]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Since no separating axis found, the OBBs must a_pOther->m_v3HalfWidth intersecting
	return true;
}