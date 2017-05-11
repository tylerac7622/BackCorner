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
	player.ChangeEuler(vector3(-fAngleX * 7.0f, 0, 0));
	player.ChangeEuler(vector3(0, fAngleY * 5.0f, 0));
	SetCursorPos(CenterX, CenterY);//Position the mouse in the center
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	//m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);
	cam.SetPosition(vector3(0.0f, 0.0f, 15.0f));
	cam.SetTarget(ZERO_V3);
	cam.SetUp(REAXISY);

	optimizer = new SpatialOpt(500, vector3(0.0f, 0.0f, 0.0f), 4);
	optimizer->SetToDraw(true);

	srand(time(NULL));

	m_pMeshMngr->LoadModel("bullet.obj", "bullet", false);
	m_pMeshMngr->InstanceCuboid(vector3(500, 0, 500), REGREEN, "ground");
	m_pMeshMngr->InstanceCuboid(vector3(60, 5, 1), REGRAY, "obstac0");
	m_pMeshMngr->InstanceCuboid(vector3(28, 4, 1), REGRAY, "obstac1");
	m_pMeshMngr->InstanceCuboid(vector3(60, 1, 60), REGRAY, "obstac2");
	m_pMeshMngr->InstanceCylinder(2, 0.5, 10, REBLUE, "target");
	m_pMeshMngr->InstanceCuboid(vector3(10, 15, 20), REBROWN, "obstac3");
	m_pMeshMngr->InstanceCuboid(vector3(10, 100, 10), RERED, "obstac4");
	m_pMeshMngr->InstanceCuboid(vector3(100, 100, 5), REYELLOW, "obstac5");
	m_pMeshMngr->InstanceCuboid(vector3(100, 100, 5), REYELLOW, "obstac6");
	m_pMeshMngr->InstanceCuboid(vector3(35, 5, 25), REWHITE, "obstac7");

	world.push_back(Object(vector3(0.0f, -2.5f, -30.0f), vector3(0.0, 0.0, 0.0), "obstac0"));
	world.push_back(Object(vector3(-16.0f, 2.0f, -30.0f), vector3(0.0, 0.0, 0.0), "obstac1"));
	world.push_back(Object(vector3(16.0f, 2.0f, -30.0f), vector3(0.0, 0.0, 0.0), "obstac1"));
	world.push_back(Object(vector3(0.0f, 6.5f, -30.0f), vector3(0.0, 0.0, 0.0), "obstac0"));

	//"left" wall
	world.push_back(Object(vector3(-30.0f, -2.5f, 0.0f), vector3(0.0, 90.0, 0.0), "obstac0"));
	world.push_back(Object(vector3(-30.0f, 2.0f, -16.0f), vector3(0.0, 90.0, 0.0), "obstac1"));
	world.push_back(Object(vector3(-30.0f, 2.0f, 16.0f), vector3(0.0, 90.0, 0.0), "obstac1"));
	world.push_back(Object(vector3(-30.0f, 6.5f, 0.0f), vector3(0.0, 90.0, 0.0), "obstac0"));

	//"back" wall
	world.push_back(Object(vector3(0.0f, -2.5f, 30.0f), vector3(0.0, 180.0, 0.0), "obstac0"));
	world.push_back(Object(vector3(16.0f, 2.0f, 30.0f), vector3(0.0, 180.0, 0.0), "obstac1"));
	world.push_back(Object(vector3(-16.0f, 2.0f, 30.0f), vector3(0.0, 180.0, 0.0), "obstac1"));
	world.push_back(Object(vector3(0.0f, 6.5f, 30.0f), vector3(0.0, 180.0, 0.0), "obstac0"));

	//"right" wall
	world.push_back(Object(vector3(30.0f, -2.5f, 0.0f), vector3(0.0, 270.0, 0.0), "obstac0"));
	world.push_back(Object(vector3(30.0f, 2.0f, 16.0f), vector3(0.0, 270.0, 0.0), "obstac1"));
	world.push_back(Object(vector3(30.0f, 2.0f, -16.0f), vector3(0.0, 270.0, 0.0), "obstac1"));
	world.push_back(Object(vector3(30.0f, 6.5f, 0.0f), vector3(0.0, 270.0, 0.0), "obstac0"));

	//"top"
	world.push_back(Object(vector3(0.0f, 9.5f, 0.0f), vector3(0.0, 0.0, 0.0), "obstac2"));

	// obstacles
	world.push_back(Object(vector3(30.0f, 2.0f, 70.0f), vector3(0.0, 0.0, 0.0), "obstac3"));
	world.push_back(Object(vector3(30.0f, 2.0f, -70.0f), vector3(0.0, 90.0, 0.0), "obstac3"));
	world.push_back(Object(vector3(-30.0f, 2.0f, 70.0f), vector3(0.0, 0.0, 0.0), "obstac3"));
	world.push_back(Object(vector3(-80.0f, 2.0f, 10.0f), vector3(0.0, 90.0, 0.0), "obstac3"));
	world.push_back(Object(vector3(60.0f, 2.0f, 10.0f), vector3(0.0, 0.0, 0.0), "obstac4"));
	world.push_back(Object(vector3(-30.0f, 2.0f, -70.0f), vector3(0.0, 0.0, 0.0), "obstac4"));
	world.push_back(Object(vector3(-10.0f, 2.0f, 70.0f), vector3(0.0, 0.0, 0.0), "obstac4"));
	world.push_back(Object(vector3(-60.0f, 2.0f, 10.0f), vector3(0.0, 0.0, 0.0), "obstac4"));
	world.push_back(Object(vector3(0.0f, 2.0f, -70.0f), vector3(0.0, 0.0, 0.0), "obstac4"));
	world.push_back(Object(vector3(100.0f, 2.0f, 70.0f), vector3(0.0, 0.0, 0.0), "obstac4"));
	world.push_back(Object(vector3(-60.0f, 2.0f, 100.0f), vector3(0.0, 0.0, 0.0), "obstac4"));
	world.push_back(Object(vector3(0.0f, 2.0f, 50.0f), vector3(0.0, 0.0, 0.0), "obstac4"));
	world.push_back(Object(vector3(100.0f, 2.0f, 0.0f), vector3(0.0, 0.0, 0.0), "obstac4"));
	world.push_back(Object(vector3(-100.0f, 2.0f, 70.0f), vector3(0.0, 90.0, 0.0), "obstac5"));
	world.push_back(Object(vector3(-105.0f, 15.0f, 70.0f), vector3(90.0, 0.0, 0.0), "obstac4"));
	world.push_back(Object(vector3(-105.0f, 30.0f, 70.0f), vector3(90.0, 0.0, 0.0), "obstac4"));
	world.push_back(Object(vector3(-110.0f, 2.0f, 70.0f), vector3(0.0, 90.0, 0.0), "obstac6"));
	
	//sky clouds
	world.push_back(Object(vector3(50.0f, 60.0f, 100.0f), vector3(0.0, 90.0, 0.0), "obstac7"));
	world.push_back(Object(vector3(52.0f, 62.0f, 100.0f), vector3(0.0, 120, 0.0), "obstac7"));
	world.push_back(Object(vector3(54.0f, 64.0f, 100.0f), vector3(0.0, 150.0, 0.0), "obstac7"));
	world.push_back(Object(vector3(56.0f, 66.0f, 100.0f), vector3(0.0, 180, 0.0), "obstac7"));
	world.push_back(Object(vector3(-50.0f, 60.0f, 50.0f), vector3(0.0, 90.0, 0.0), "obstac7"));
	world.push_back(Object(vector3(-52.0f, 62.0f, 50.0f), vector3(0.0, 120, 0.0), "obstac7"));
	world.push_back(Object(vector3(-54.0f, 64.0f, 50.0f), vector3(0.0, 150.0, 0.0), "obstac7"));
	world.push_back(Object(vector3(-56.0f, 66.0f, 50.0f), vector3(0.0, 180, 0.0), "obstac7"));
	world.push_back(Object(vector3(-50.0f, 60.0f, -25.0f), vector3(0.0, 90.0, 0.0), "obstac7"));
	world.push_back(Object(vector3(-52.0f, 62.0f, -25.0f), vector3(0.0, 120, 0.0), "obstac7"));
	world.push_back(Object(vector3(-54.0f, 64.0f, -25.0f), vector3(0.0, 150.0, 0.0), "obstac7"));
	world.push_back(Object(vector3(-56.0f, 66.0f, -25.0f), vector3(0.0, 180, 0.0), "obstac7"));

	targets.push_back(Target(vector3(-20.0f, 2.0f, -50.0f), vector3(0.0, 0.0, 90.0)));
	targets.push_back(Target(vector3(-20.0f, 2.0f, -50.0f), vector3(0.0, 0.0, 90.0)));
	targets.push_back(Target(vector3(66.0f, 76.0f, 110.0f), vector3(0.0, 0.0, 90.0)));
	targets.push_back(Target(vector3(-105.0f, 40.0f, 70.0f), vector3(90.0, .0, 90.0)));
	targets.push_back(Target(vector3(-105.0f, 22.5f, 70.0f), vector3(90.0, .0, 90.0)));

	player.Init();

	m_pLightMngr->AddLight();
	m_pLightMngr->AddLight();
	m_pLightMngr->SetIntensity(100000, 1);
	m_pLightMngr->SetPosition(vector3(300.0f, 300.0f, 300.0f), 1);
	m_pLightMngr->SetIntensity(10, 2);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	bullet.collider = new MyBoundingBoxClass(m_pMeshMngr->GetInstanceByName("bullet")->GetVertexList(), 1);

	for (int i = 0; i < world.size(); i++)
	{
		world[i].collider = new MyBoundingBoxClass(m_pMeshMngr->GetInstanceByName(world[i].GetName())->GetVertexList(), 1);
		world[i].Update(globalTime);
	}
	for (int i = 0; i < targets.size(); i++)
	{
		targets[i].collider = new MyBoundingBoxClass(m_pMeshMngr->GetInstanceByName(targets[i].GetName())->GetVertexList(), 1);
		targets[i].Update(globalTime);
	}

	for (int i = 0; i < world.size(); i++)
	{
		optimizer->PlaceObject(&world[i]);
	}
	for (int i = 0; i < targets.size(); i++)
	{
		optimizer->PlaceTarget(&targets[i]);
	}
}

void AppClass::Update(void)
{
	static vector3 startLocation = vector3(target.GetPosition().x, target.GetPosition().y, target.GetPosition().z);
	static vector3 endLoaction = vector3(target.GetPosition().x, target.GetPosition().y + 6.0f, target.GetPosition().z);
	static vector3 negStartLocation = vector3(target.GetPosition().x, target.GetPosition().y + 6.0f, target.GetPosition().z);
	static vector3 negEndLoaction = vector3(target.GetPosition().x, target.GetPosition().y, target.GetPosition().z);

	//m_pLightMngr->SetPosition(player.GetPosition(), 0);
	m_pLightMngr->SetPosition(bullet.GetPosition(), 2);


	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	//m_pMeshMngr->AddSkyboxToRenderList();

	bullet.Update(globalTime);
	m_pMeshMngr->SetModelMatrix(bullet.GetWorldMatrix(), "bullet");
	optimizer->GetPlacement(&bullet);
	//target.Update(globalTime);
	//m_pMeshMngr->SetModelMatrix(target.GetWorldMatrix(), "target");
	//m_pMeshMngr->AddInstanceToRenderList("target");
	player.Update(globalTime);
	optimizer->GetPlacement(&player);
	for (int i = 0; i < world.size(); i++)
	{
		world[i].Update(globalTime);
		m_pMeshMngr->SetModelMatrix(world[i].GetWorldMatrix(),  world[i].GetName());
		m_pMeshMngr->AddInstanceToRenderList( world[i].GetName());
		m_pMeshMngr->AddInstanceToRenderList("crosshair");
	}
	for (int i = 0; i < targets.size(); i++)
	{
		targets[i].Update(globalTime);
		m_pMeshMngr->SetModelMatrix(targets[i].GetWorldMatrix(), targets[i].GetName());
		m_pMeshMngr->AddInstanceToRenderList(targets[i].GetName());
	}

	//limits the bullet and resets it if it goes too far
	if (abs(bullet.GetPosition().x) + abs(bullet.GetPosition().z) > 700)
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

	if (bullet.GetFired())
	{
		//Adds the bullet model to the render list
		m_pMeshMngr->AddInstanceToRenderList("bullet");
	}

	//First person camera movement
	if (m_bFPC == true)
		RotateCam();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

	int collisionChecks = 0;
	//update bullet collis
	if (bullet.GetFired())
	{
		for (int i = 0; i < bullet.currentSpec.size(); i++)
		{
			if (bullet.currentSpec[i]->content.size() > 0)
			{
				for (int i2 = 0; i2 < bullet.currentSpec[i]->content.size(); i2++)
				{
					collisionChecks++;
					if (bullet.collider->IsColliding(bullet.currentSpec[i]->content[i2]->collider))
					{
						bullet.Reset(vector3(0, 2, 0), vector3(0, 0, 0));
						followBullet = false;
						globalTime = 1;
					}
				}
			}
			if (bullet.currentSpec[i]->targets.size() > 0)
			{
				for (int i2 = 0; i2 < bullet.currentSpec[i]->targets.size(); i2++)
				{
					collisionChecks++;
					if (bullet.collider->IsColliding(bullet.currentSpec[i]->targets[i2]->collider))
					{
						Target* saveTarget = bullet.currentSpec[i]->targets[i2];
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
						optimizer->RemoveFromTargets(saveTarget);
						saveTarget->SetPosition(vector3(posX, 2, posZ));
						saveTarget->currentSpec.clear();
						optimizer->PlaceTarget(saveTarget);

						bullet.Reset(vector3(0, 2, 0), vector3(0, 0, 0));
						followBullet = false;
						globalTime = 1;
						hitTarget = true;
						timer = 0.0f;
						score++;
					}
				}
			}
		}
	}

	player.collider->SetColliding(false);
	for (int i = 0; i < player.currentSpec.size(); i++)
	{
		if (player.currentSpec[i]->content.size() > 0)
		{
			for (int i2 = 0; i2 < player.currentSpec[i]->content.size(); i2++)
			{
				collisionChecks++;
				if (player.collider->IsColliding(player.currentSpec[i]->content[i2]->collider))
				{
					player.collider->SetColliding(true);
				}
			}
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

	//target.SetPosition(lerpedLocation);
	/*
	if (player.collider->GetColliding())
	{
		player.ChangePosition(quaternion(vector3(0, PI *player.GetEuler().y / 180, 0)) * -player.GetVelocity() * globalTime);
	}
	*/
	player.SetVelocity(vector3(0, 0, 0));

	int fps = m_pSystem->GetFPS();
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->Print("                             Time: " + std::to_string(fRunTime));
	m_pMeshMngr->Print("                     FPS: " + std::to_string(fps), REYELLOW);
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->Print("Targets Left: ");
	m_pMeshMngr->Print(std::to_string(targets.size()));
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->Print("Score: ");
	m_pMeshMngr->Print(std::to_string(score));
	m_pMeshMngr->PrintLine("");
	if (hitTarget) {
		timer++;
		m_pMeshMngr->PrintLine("                               TARGET HIT", REBLUE);
		m_pMeshMngr->Print("                                    +1", REBLUE);
		if (timer > timeCheck) {
			hitTarget = false;
		}
	}


	

	/*Debug lines
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->Print("Position:");
	m_pMeshMngr->Print(std::to_string(player.collider->GetCenterGlobal().x) + ", ");
	m_pMeshMngr->Print(std::to_string(player.collider->GetCenterGlobal().y) + ", ");
	m_pMeshMngr->PrintLine(std::to_string(player.collider->GetCenterGlobal().z));
	m_pMeshMngr->Print("Euler:");
	m_pMeshMngr->Print(std::to_string(player.GetEuler().x) + ", ");
	m_pMeshMngr->Print(std::to_string(player.GetEuler().y) + ", ");
	m_pMeshMngr->PrintLine(std::to_string(player.GetEuler().z));
	m_pMeshMngr->PrintLine("");
	if (followBullet)
	{
		m_pMeshMngr->PrintLine("FOLLOWING BULLET");
	}
	//m_pMeshMngr->PrintLine("Hold right click to free mouse");
	m_pMeshMngr->Print("Collisions Being Checked : ");
	m_pMeshMngr->PrintLine(std::to_string(collisionChecks));
	*/
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	matrix4 groundMatrix = IDENTITY_M4;
	groundMatrix = glm::translate(vector3(0, -5, 0));
	//quaternion q = glm::angleAxis(90.0f, vector3(1.0f, 0.0f, 0.0f));
	quaternion q = glm::angleAxis(0.0f, vector3(1.0f, 0.0f, 0.0f));
	groundMatrix *= ToMatrix4(q);

	m_pMeshMngr->SetModelMatrix(groundMatrix, "ground");

	m_pMeshMngr->AddInstanceToRenderList("ground");

	//following the bullet
	if (followBullet)
	{
		m_pCameraMngr->SetPositionTargetAndView(bullet.GetCamera().GetPosition(), bullet.GetCamera().GetTarget(), bullet.GetCamera().GetUp());

		if (bullet.GetFired())
		{
			//bullet.model->Render(bullet.GetCamera().GetProjection(false), bullet.GetCamera().GetView(), bullet.GetWorldMatrix());
		}
	}
	//fps player camera
	if(!followBullet)
	{
		m_pCameraMngr->SetPositionTargetAndView(player.GetCamera().GetPosition(), player.GetCamera().GetTarget(), player.GetCamera().GetUp());

		if (bullet.GetFired())
		{
			//bullet.model->Render(player.GetCamera().GetProjection(false), player.GetCamera().GetView(), bullet.GetWorldMatrix());
		}
	}

	optimizer->DrawAllPartions();

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers

}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}