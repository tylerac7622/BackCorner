#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - YOUR USER NAME GOES HERE"); // Window Name

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
	cam.ChangeYaw(fAngleY * 3.0f);
	cam.ChangePitch(-fAngleX * 3.0f);
	SetCursorPos(CenterX, CenterY);//Position the mouse in the center
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	//m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);
	cam.SetPosition(vector3(0.0f, 0.0f, 15.0f));
	cam.SetTarget(ZERO_V3);
	cam.SetUp(REAXISY);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	//Setting the days duration
	m_fDay = 1.0f;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		RotateCam();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

	//Earth Orbit
	double fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route

	glm::mat4 m4Sun = glm::scale(5.936f, 5.936f, 5.936f);
	
	glm::quat quat1 = glm::angleAxis(0.0f, vector3(0.0f, 1.0f, 0.0f));
	glm::quat quat2 = glm::angleAxis(359.0f, vector3(0.0f, 1.0f, 0.0f));
	glm::quat orbitQuat = glm::mix(quat1, quat2, MapValue((float)fRunTime, 0.0f, (float)fEarthHalfOrbTime * 2, 0.0f, 1.0f));
	glm::mat4 m4Earth = glm::mat4_cast(orbitQuat);
	
	m4Earth *= glm::translate(11.0f, 0.0f, 0.0f);

	glm::mat4 m4Moon = m4Earth;

	glm::quat revQuat = glm::mix(quat1, quat2, MapValue((float)fRunTime, 0.0f, (float)fEarthHalfRevTime * 2, 0.0f, 1.0f));
	m4Earth *= glm::mat4_cast(revQuat);

	m4Earth *= glm::scale(0.524f, 0.524f, 0.524f);

	glm::quat moonOrbitQuat = glm::mix(quat1, quat2, MapValue((float)fRunTime, 0.0f, (float)fMoonHalfOrbTime * 2, 0.0f, 1.0f));
	m4Moon *= glm::mat4_cast(moonOrbitQuat);
	m4Moon *= glm::translate(2.0f, 0.0f, 0.0f);
	m4Moon *= glm::scale(0.27f, 0.27f, 0.27f);
	
	//Setting the matrices
	m_pMeshMngr->SetModelMatrix(m4Sun, "Sun");
	m_pMeshMngr->SetModelMatrix(m4Earth, "Earth");
	m_pMeshMngr->SetModelMatrix(m4Moon, "Moon");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");


	static int nEarthOrbits = 0;
	static int nEarthRevolutions = 0;
	static int nMoonOrbits = 0;

	nEarthOrbits = fRunTime / (fEarthHalfOrbTime * 2);
	nEarthRevolutions = fRunTime / (fEarthHalfRevTime * 2);
	nMoonOrbits = fRunTime / (fMoonHalfOrbTime * 2);

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	PrimitiveClass cube;
	cube.GenerateCube(5, RERED);
	cube.Render(cam.GetProjection(false), cam.GetView(), IDENTITY_M4);

	//Render the grid based on the camera's mode:
	/*
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	*/
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers

}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}