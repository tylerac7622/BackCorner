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

	//"front" wall
	world.push_back(Target(vector3(0.0f, -2.5f, -30.0f), vector3(0.0, 0.0, 0.0)));
	world.push_back(Target(vector3(-16.0f, 2.0f, -30.0f), vector3(0.0, 0.0, 0.0)));
	world.push_back(Target(vector3(16.0f, 2.0f, -30.0f), vector3(0.0, 0.0, 0.0)));
	world.push_back(Target(vector3(0.0f, 6.5f, -30.0f), vector3(0.0, 0.0, 0.0)));

	//"left" wall
	world.push_back(Target(vector3(-30.0f, -2.5f, 0.0f), vector3(0.0, 90.0, 0.0)));
	world.push_back(Target(vector3(-30.0f, 2.0f, -16.0f), vector3(0.0, 90.0, 0.0)));
	world.push_back(Target(vector3(-30.0f, 2.0f, 16.0f), vector3(0.0, 90.0, 0.0)));
	world.push_back(Target(vector3(-30.0f, 6.5f, 0.0f), vector3(0.0, 90.0, 0.0)));

	//"back" wall
	world.push_back(Target(vector3(0.0f, -2.5f, 30.0f), vector3(0.0, 180.0, 0.0)));
	world.push_back(Target(vector3(16.0f, 2.0f, 30.0f), vector3(0.0, 180.0, 0.0)));
	world.push_back(Target(vector3(-16.0f, 2.0f, 30.0f), vector3(0.0, 180.0, 0.0)));
	world.push_back(Target(vector3(0.0f, 6.5f, 30.0f), vector3(0.0, 180.0, 0.0)));

	//"right" wall
	world.push_back(Target(vector3(30.0f, -2.5f, 0.0f), vector3(0.0, 270.0, 0.0)));
	world.push_back(Target(vector3(30.0f, 2.0f, 16.0f), vector3(0.0, 270.0, 0.0)));
	world.push_back(Target(vector3(30.0f, 2.0f, -16.0f), vector3(0.0, 270.0, 0.0)));
	world.push_back(Target(vector3(30.0f, 6.5f, 0.0f), vector3(0.0, 270.0, 0.0)));

	//"top"
	world.push_back(Target(vector3(0.0f, 9.5f, 0.0f), vector3(0.0, 0.0, 0.0)));

	bullet.InitBullet();
	world[0].InitTarget(vector3(60, 5, 1));
	world[1].InitTarget(vector3(28, 4, 1));
	world[2].InitTarget(vector3(28, 4, 1));
	world[3].InitTarget(vector3(60, 5, 1));

	world[4].InitTarget(vector3(60, 5, 1));
	world[5].InitTarget(vector3(28, 4, 1));
	world[6].InitTarget(vector3(28, 4, 1));
	world[7].InitTarget(vector3(60, 5, 1));

	world[8].InitTarget(vector3(60, 5, 1));
	world[9].InitTarget(vector3(28, 4, 1));
	world[10].InitTarget(vector3(28, 4, 1));
	world[11].InitTarget(vector3(60, 5, 1));

	world[12].InitTarget(vector3(60, 5, 1));
	world[13].InitTarget(vector3(28, 4, 1));
	world[14].InitTarget(vector3(28, 4, 1));
	world[15].InitTarget(vector3(60, 5, 1));

	world[16].InitTarget(vector3(60, 1, 60));
	
	target.InitTarget(vector2(2, .5));
	player.InitPlayer();

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::Update(void)
{
	static vector3 startLocation = vector3(target.GetPosition().x, target.GetPosition().y, target.GetPosition().z);
	static vector3 endLoaction = vector3(target.GetPosition().x, target.GetPosition().y + 6.0f, target.GetPosition().z);
	static vector3 negStartLocation = vector3(target.GetPosition().x, target.GetPosition().y + 6.0f, target.GetPosition().z);
	static vector3 negEndLoaction = vector3(target.GetPosition().x, target.GetPosition().y, target.GetPosition().z);

	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	bullet.Update(globalTime);
	target.Update(globalTime);
	player.Update(globalTime);
	for (int i = 0; i < world.size(); i++)
	{
		world[i].Update(globalTime);
	}

	//limits the bullet and resets it if it goes too far
	if (bullet.GetPosition().x + bullet.GetPosition().z > 500)
	{
		bullet.Reset(vector3(0, 2, 0), vector3(0, 0, 0));
		followBullet = false;
		globalTime = 1;
	}
	if (bullet.GetPosition().y <= -5)
	{
		bullet.Reset(vector3(0, 2, 0), vector3(0, 0, 0));
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

		int posX = rand() % 130;
		int posZ = rand() % 130;
		if (posX < 65)
		{
			posX = -100 + posX;
		}
		else
		{
			posX = 100 - (posX - 65);
		}
		if (posZ < 65)
		{
			posZ = -100 + posZ;
		}
		else
		{
			posZ = 100 - (posZ - 65);
		}
		target.SetPosition(vector3(posX, 2, posZ));
		target.SetEuler(vector3(0, 0, 90.0f));

		bullet.Reset(vector3(0, 2, 0), vector3(0, 0, 0));
		followBullet = false;
		globalTime = 1;

		startLocation = vector3(target.GetPosition().x, target.GetPosition().y, target.GetPosition().z);
		endLoaction = vector3(target.GetPosition().x, target.GetPosition().y + 6.0f, target.GetPosition().z);
		negStartLocation = vector3(target.GetPosition().x, target.GetPosition().y + 6.0f, target.GetPosition().z);
		negEndLoaction = vector3(target.GetPosition().x, target.GetPosition().y, target.GetPosition().z);
	}
	else {
		target.model->GenerateCylinder(2.0f, 0.5f, 10, REBLUE);
	}

	for (int i = 0; i < world.size(); i++)
	{
		if (bullet.collider->IsColliding(world[i].collider))
		{
			bullet.Reset(vector3(0, 2, 0), vector3(0, 0, 0));
			followBullet = false;
			globalTime = 1;
		}
	}

	static bool up = true;
	static bool down = false;

	const float translationTime = 1.5f;
	static int translationClockIndex = m_pSystem->GenClock();
	static float translationTimer = 0.0f;
	translationTimer += m_pSystem->LapClock(translationClockIndex);
	float locationMaped = MapValue(translationTimer, 0.0f, translationTime, 0.0f, 1.0f);

	vector3 lerpedLocation;

	if (up) {
		lerpedLocation = glm::lerp(startLocation, endLoaction, locationMaped);
	}
	if (down) {
		lerpedLocation = glm::lerp(negStartLocation, negEndLoaction, locationMaped);
	}

	if (locationMaped >= 1.0f) {
		translationTimer = 0.0f;

		if (up) {
			up = false;
			down = true;
		}
		else if (down) {
			down = false;
			up = true;
		}
	}

	target.SetPosition(lerpedLocation);

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
	//m_pMeshMngr->PrintLine("Hold right click to free mouse");
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
		for (int i = 0; i < world.size(); i++)
		{
			world[i].model->Render(bullet.GetCamera().GetProjection(false), bullet.GetCamera().GetView(), world[i].GetWorldMatrix());
		}
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
		for (int i = 0; i < world.size(); i++)
		{
			world[i].model->Render(player.GetCamera().GetProjection(false), player.GetCamera().GetView(), world[i].GetWorldMatrix());
		}
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