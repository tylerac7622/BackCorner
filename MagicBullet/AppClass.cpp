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
	player.ChangeEuler(vector3(-fAngleX * 5.0f, 0, 0));
	player.ChangeEuler(vector3(0, fAngleY * 4.0f, 0));
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

	//ground
	m_pGround = new PrimitiveClass();
	m_pGround->GeneratePlane(200.0f, REGREEN);

	bullet.InitBullet();
	target.InitTarget();
	player.InitPlayer();

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
	target.Update(globalTime);
	player.Update(globalTime);

	//limits the bullet and resets it if it goes too far
	if (bullet.GetPosition().x + bullet.GetPosition().z > 500)
	{
		bullet.Reset();
		followBullet = false;
		globalTime = 1;
	}
	if (bullet.GetPosition().y <= -5)
	{
		bullet.Reset();
		followBullet = false;
		globalTime = 1;
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
	if (bullet.collider->IsColliding(target.collider))
	{
		target.model->GenerateCylinder(2.0f, 0.5f, 10, RERED);

		target.SetPosition(vector3(rand() % 200 - 100, 2, rand() % 200 - 100));
		target.SetEuler(vector3(0, 0, 90.0f));

		bullet.Reset();
		followBullet = false;
		globalTime = 1;
	}
	else {
		target.model->GenerateCylinder(2.0f, 0.5f, 10, REBLUE);
	}

	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->Print("Position:");
	m_pMeshMngr->Print(std::to_string(player.GetCamera().GetPosition().x) + ", ");
	m_pMeshMngr->Print(std::to_string(player.GetCamera().GetPosition().y) + ", ");
	m_pMeshMngr->PrintLine(std::to_string(player.GetCamera().GetPosition().z));
	m_pMeshMngr->Print("Euler:");
	m_pMeshMngr->Print(std::to_string(player.GetEuler().x) + ", ");
	m_pMeshMngr->Print(std::to_string(player.GetEuler().y) + ", ");
	m_pMeshMngr->PrintLine(std::to_string(player.GetEuler().z));
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine("Press Escape to quit");
	m_pMeshMngr->PrintLine("Hold right click to free mouse");
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

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
			bullet.model->Render(bullet.GetCamera().GetProjection(false), bullet.GetCamera().GetView(), bullet.GetWorldMatrix());
		}
		m_pGround->Render(bullet.GetCamera().GetProjection(false), bullet.GetCamera().GetView(), groundMatrix);
		target.model->Render(bullet.GetCamera().GetProjection(false), bullet.GetCamera().GetView(), target.GetWorldMatrix());
		m_pGround2->Render(bullet.GetCamera().GetProjection(false), bullet.GetCamera().GetView(), groundMatrix2);
	}
	//fps player camera
	if(!followBullet)
	{
		if (bullet.GetFired())
		{
			bullet.model->Render(player.GetCamera().GetProjection(false), player.GetCamera().GetView(), bullet.GetWorldMatrix());
		}
		m_pGround->Render(player.GetCamera().GetProjection(false), player.GetCamera().GetView(), groundMatrix);
		target.model->Render(player.GetCamera().GetProjection(false), player.GetCamera().GetView(), target.GetWorldMatrix());
		m_pGround2->Render(player.GetCamera().GetProjection(false), player.GetCamera().GetView(), groundMatrix2);
	}

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers

}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}