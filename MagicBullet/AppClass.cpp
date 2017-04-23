#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Magic Bullet - Back Corner"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::RotateCam(float a_fSpeed = 0.005f)
{
	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

								//Initialize the position of the pointer to the middle of the screen
	CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
	CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;

	//Calculate the position of the mouse and store it
	POINT pt;
	GetCursorPos(&pt);
	MouseX = pt.x;
	MouseY = pt.y;

	//Calculate the difference in view with the angle
	float fAngleX = 0.0f;
	float fAngleY = 0.0f;
	float fDeltaMouse = 0.0f;
	if (MouseX < CenterX)
	{
		fDeltaMouse = static_cast<float>(CenterX - MouseX);
		fAngleY += fDeltaMouse * a_fSpeed;
	}
	else if (MouseX > CenterX)
	{
		fDeltaMouse = static_cast<float>(MouseX - CenterX);
		fAngleY -= fDeltaMouse * a_fSpeed;
	}

	if (MouseY < CenterY)
	{
		fDeltaMouse = static_cast<float>(CenterY - MouseY);
		fAngleX -= fDeltaMouse * a_fSpeed;
	}
	else if (MouseY > CenterY)
	{
		fDeltaMouse = static_cast<float>(MouseY - CenterY);
		fAngleX += fDeltaMouse * a_fSpeed;
	}
	//Change the Yaw and the Pitch of the camera
	cam.ChangeYaw(-fAngleY * 3.0f);
	cam.ChangePitch(fAngleX * 3.0f);
	SetCursorPos(CenterX, CenterY);//Position the mouse in the center
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	//m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);
	cam.SetPosition(vector3(0.0f, 0.0f, 15.0f));
	cam.SetTarget(ZERO_V3);
	cam.SetUp(REAXISY);

	srand(time(NULL));

	//bullet
	m_pCone = new PrimitiveClass();
	m_pCone->GenerateCone(1.0f, 1.0f, 10, RERED);

	//ground
	m_pGround = new PrimitiveClass();
	m_pGround->GeneratePlane(200.0f, REGREEN);

	//target cylinder
	m_pTarget = new PrimitiveClass();
	m_pTarget->GenerateCylinder(2.0f, 0.5f, 10, REBLUE);

	bulletCollider = new MyBoundingBoxClass(m_pCone->GetVertexList());
	bulletCollider->SetColliding(false);

	targetCollider = new MyBoundingBoxClass(m_pTarget->GetVertexList());
	targetCollider->SetColliding(false);

	targetMatrix = glm::translate(vector3(-30, 2, -70));
	quaternion q2 = glm::angleAxis(90.0f, vector3(0.0f, 0.0f, 1.0f));
	targetMatrix *= ToMatrix4(q2);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	bullet.Update(globalTime);

	//limits the bullet and resets it if it goes too far
	if (bullet.GetPosition().x + bullet.GetPosition().z > 500)
	{
		bullet = Bullet();
	}

	//First person camera movement
	if (m_bFPC == true)
		RotateCam();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

	//update bullet collis
	bulletCollider->SetModelMatrix(bulletMatrix);
	targetCollider->SetModelMatrix(targetMatrix);
	if (bulletCollider->IsColliding(targetCollider)) 
	{
		m_pTarget->GenerateCylinder(2.0f, 0.5f, 10, RERED);

		targetMatrix = glm::translate(vector3(rand() % 200 - 100, 2, rand() % 200 - 100));
		quaternion q2 = glm::angleAxis(90.0f, vector3(0.0f, 0.0f, 1.0f));
		targetMatrix *= ToMatrix4(q2);
	}
	else {
		m_pTarget->GenerateCylinder(2.0f, 0.5f, 10, REBLUE);
	}

	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->Print("Rotation:");
	m_pMeshMngr->Print(std::to_string(bullet.GetEuler().x) + ", ");
	m_pMeshMngr->Print(std::to_string(bullet.GetEuler().y) + ", ");
	m_pMeshMngr->PrintLine(std::to_string(bullet.GetEuler().z));
	m_pMeshMngr->Print("Up:");
	m_pMeshMngr->Print(std::to_string(cam.GetUp().x) + ", ");
	m_pMeshMngr->Print(std::to_string(cam.GetUp().y) + ", ");
	m_pMeshMngr->PrintLine(std::to_string(cam.GetUp().z));
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the cone
	
	bulletMatrix = glm::translate(bullet.GetPosition());
	bulletMatrix *= ToMatrix4(bullet.GetRotation());

	matrix4 groundMatrix = IDENTITY_M4;
	groundMatrix = glm::translate(vector3(0, -5, 0));
	quaternion q = glm::angleAxis(90.0f, vector3(1.0f, 0.0f, 0.0f));
	groundMatrix *= ToMatrix4(q);

	PrimitiveClass* m_pGround2 = new PrimitiveClass();
	m_pGround2->GeneratePlane(200.0f, RERED);
	matrix4 groundMatrix2 = IDENTITY_M4;
	groundMatrix2 = glm::translate(vector3(0, -6, 0));
	quaternion q2 = glm::angleAxis(90.0f, vector3(1.0f, 0.0f, 0.0f));
	groundMatrix2 *= ToMatrix4(q2);

	//following the bullet
	if (followBullet)
	{
		if (bullet.GetFired())
		{
			m_pCone->Render(bullet.GetCamera().GetProjection(false), bullet.GetCamera().GetView(), bulletMatrix);
		}
		m_pGround->Render(bullet.GetCamera().GetProjection(false), bullet.GetCamera().GetView(), groundMatrix);
		m_pTarget->Render(bullet.GetCamera().GetProjection(false), bullet.GetCamera().GetView(), targetMatrix);
		m_pGround2->Render(bullet.GetCamera().GetProjection(false), bullet.GetCamera().GetView(), groundMatrix2);
	}
	//fps player camera
	if(!followBullet)
	{
		if (bullet.GetFired())
		{
			m_pCone->Render(cam.GetProjection(false), cam.GetView(), bulletMatrix);
		}
		m_pGround->Render(cam.GetProjection(false), cam.GetView(), groundMatrix);
		m_pTarget->Render(cam.GetProjection(false), cam.GetView(), targetMatrix);
		m_pGround2->Render(cam.GetProjection(false), cam.GetView(), groundMatrix2);
	}

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers

}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}