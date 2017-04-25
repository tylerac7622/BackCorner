#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Bounding Object Manager"); // Window Name 

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	m_bArcBallZ = false;

	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 0.0f);

	m_pPlane = new PrimitiveClass();
	m_pPlane->GeneratePlane(5.0f, REYELLOW);

	//Load Models
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper");

	m_pBOMngr = MyBOManager::GetInstance();
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("Steve"), "Steve");
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("Creeper"), "Creeper");
}

void CheckSAT(void)
{
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();
	ArcBallZ();

	//Object Movement
	static float fTimer = 0.0f;
	static int nClock = m_pSystem->GenClock();
	float fDeltaTime = static_cast<float>(m_pSystem->LapClock(nClock));
	fTimer += fDeltaTime;

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Creeper");

	//Set the model matrix to the Bounding Object
	m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Steve"), "Steve");
	m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Creeper"), "Creeper");

	m_pBOMngr->Update();//Update collision detection
	
	//m_pBOMngr->DisplaySphere(-1, REWHITE);
	m_pBOMngr->DisplayReAlligned();
	m_pBOMngr->DisplayOriented(-1, REWHITE);

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	CheckSAT();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	std::vector<int> list = m_pBOMngr->GetCollidingVector(0);
	m_pMeshMngr->Print("Object 0 colliding with: ", REBLUE);
	for (uint n = 0; n < list.size(); n++)
	{
		m_pMeshMngr->Print(std::to_string(list[n]) + " ", REYELLOW);
	}

	m_pMeshMngr->PrintLine(" ");
	
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);

	m_pMeshMngr->PrintLine(" ");

	m_pMeshMngr->Print("Dot:");
	m_pMeshMngr->Print(std::to_string(glm::dot(glm::normalize(m_v3O1), glm::normalize(m_v3O2))), RERED);
}

void AppClass::Display(void)
{
	//Ok, here's how this fun stuff works
	matrix4 planeMatrix = IDENTITY_M4;

	//get steve and creeper centers, for the sake of using easier variables
	vector3 creeperCenter = m_pBOMngr->GetBoundingObject("Creeper")->GetCenterGlobal();
	vector3 steveCenter = m_pBOMngr->GetBoundingObject("Steve")->GetCenterGlobal();
	//finding the global center point between both objects
	vector3 centerPos = vector3((steveCenter.x + creeperCenter.x)/2, (steveCenter.y + creeperCenter.y) / 2, (steveCenter.z + creeperCenter.z) / 2);
	//move the plane to the global center pos
	planeMatrix = glm::translate(centerPos);
	//find the vector between the center points of both objects, multiplied by steve's rotation
	vector3 vectorBetween = vector3((steveCenter.x - creeperCenter.x), (steveCenter.y - creeperCenter.y), (steveCenter.z - creeperCenter.z)) * m_qArcBall;
	//absolute value the vector, since we only care about positive numbers
	vectorBetween = vector3(abs(vectorBetween.x), abs(vectorBetween.y), abs(vectorBetween.z));
	quaternion q;
	//if the vectorBetween's x is the largest, the plane is on the x axis
	if (vectorBetween.x >= vectorBetween.y && vectorBetween.x >= vectorBetween.z)
	{
		q = glm::angleAxis(90.0f, vector3(0.0f, 1.0f, 0.0f));
		m_pPlane->GeneratePlane(5.0f, RERED);
	}
	//if the vectorBetween's y is the largest, the plane is on the y axis
	if (vectorBetween.y >= vectorBetween.x && vectorBetween.y > vectorBetween.z)
	{
		q = glm::angleAxis(90.0f, vector3(1.0f, 0.0f, 0.0f));
		m_pPlane->GeneratePlane(5.0f, REGREEN);
	}
	//if the vectorBetween's z is the largest, the plane is on the z axis
	if (vectorBetween.z > vectorBetween.x && vectorBetween.z > vectorBetween.y)
	{
		q = glm::angleAxis(90.0f, vector3(0.0f, 0.0f, 1.0f));
		m_pPlane->GeneratePlane(5.0f, REBLUE);
	}

	//rotate the place by the rotation of steve
	planeMatrix *= ToMatrix4(m_qArcBall * q);

	//clear the screen
	ClearScreen();

	m_pPlane->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), planeMatrix);
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
	MyBOManager::ReleaseInstance();
}

void AppClass::ArcBallZ(float a_fSensitivity)
{
	//If the arcball is not enabled return
	if (!m_bArcBallZ)
		return;

	//static quaternion qArcBall;
	UINT	MouseX, MouseY;		// Coordinates for the mouse

	//Calculate the position of the mouse and store it
	POINT pt;
	GetCursorPos(&pt);
	MouseX = pt.x;
	MouseY = pt.y;

	if (MouseLastX != 0 && MouseLastY != 0)
	{
		//Calculate the difference in position and update the quaternion orientation based on it
		float DeltaMouse;
		if (MouseX < MouseLastX)
		{
			DeltaMouse = static_cast<float>(MouseLastX - MouseX);
			m_qArcBall = quaternion(vector3(0.0f, 0.0f, glm::radians(a_fSensitivity * DeltaMouse))) * m_qArcBall;
		}
		else if (MouseX > MouseLastX)
		{
			DeltaMouse = static_cast<float>(MouseX - MouseLastX);
			m_qArcBall = quaternion(vector3(0.0f, 0.0f, glm::radians(-a_fSensitivity * DeltaMouse))) * m_qArcBall;
		}
	}
	SetCursorPos(MouseLastX, MouseLastY);
}