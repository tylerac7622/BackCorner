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
	cam.SetPosition(vector3(0.0f, 0.0f, 15.0f));
	cam.SetTarget(ZERO_V3);
	cam.SetUp(REAXISY);

	//bullet
	m_pCone = new PrimitiveClass();
	m_pCone->GenerateCone(1.0f, 1.0f, 10, RERED);

	//ground
	m_pGround = new PrimitiveClass();
	m_pGround->GeneratePlane(200.0f, REGREEN);

	//target cylinder
	m_pTarget = new PrimitiveClass();
	m_pTarget->GenerateCylinder(2.0f, 0.5f, 10, REBLUE);

	m_pMeshMngr->LoadModel("bullet.obj", "bullet");

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	bullet.Update(globalTime);

	//limits the bullet and resets it if it goes too far
	if (bullet.GetPosition().x + bullet.GetPosition().z > 500)
	{
		bullet = Bullet();
	}

	//First person camera movement
	if (m_bFPC == true)
		RotateCam();

	bulletMatrix = glm::translate(bullet.GetPosition());

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	
	//m_pMeshMngr->SetModelMatrix(m4Bullet, "bullet");

	//Render the cone
	//matrix4 bulletMatrix = IDENTITY_M4;
	//bulletMatrix = glm::translate(bullet.GetPosition());

	m_pMeshMngr->SetModelMatrix(bulletMatrix, "bullet");

	matrix4 groundMatrix = IDENTITY_M4;
	groundMatrix = glm::translate(vector3(0, -5, 0));
	quaternion q = glm::angleAxis(90.0f, vector3(1.0f, 0.0f, 0.0f));
	groundMatrix *= ToMatrix4(q);

	matrix4 targetMatrix = IDENTITY_M4;
	targetMatrix = glm::translate(vector3(-30, 2, -70));
	quaternion q2 = glm::angleAxis(90.0f, vector3(0.0f, 0.0f, 1.0f));
	targetMatrix *= ToMatrix4(q2);

	//following the bullet
	if (followBullet)
	{
		if (bullet.GetFired())
		{
			m_pCone->Render(bullet.GetCamera().GetProjection(false), bullet.GetCamera().GetView(), bulletMatrix);
		}
		m_pGround->Render(bullet.GetCamera().GetProjection(false), bullet.GetCamera().GetView(), groundMatrix);
		m_pTarget->Render(bullet.GetCamera().GetProjection(false), bullet.GetCamera().GetView(), targetMatrix);
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
	}

	//m_pCameraMngr->SetPositionTargetAndView(bullet.GetPosition(), ZERO_V3, REAXISY);

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers

}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}