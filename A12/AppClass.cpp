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
	//spaceOptimzer = new SpatialOpt(500, vector3(0.0f, 0.0f, 0.0f), 8);
	spaceOptimzer = new SpatialOpt(100, vector3(0.0f, 0.0f, -50.0f), 4);
	spaceOptimzer->SetToDraw(true);
	//spaceOptimzer->GeneratePartionCenters();

	m_bArcBallZ = false;

	//Load Models
	for (int i = 0; i < numObjects; i++) {
		m_pMeshMngr->LoadModel("Minecraft\\Cow.obj", std::to_string(i));
	}

	m_pBOMngr = MyBOManager::GetInstance();
	
	for (int i = 0; i < numObjects; i++) {
		m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList(std::to_string(i)), std::to_string(i));
	}

	for (int i = 0; i < numObjects; i++) {
		float x = rand() % 100;
		float y = rand() % 100;
		float z = rand() % 100;
		z -= 50;
		//x = 60 + (i*.5f);
		//y = 60;
		//z = 60;

		m_pMeshMngr->SetModelMatrix(glm::translate(vector3((float)x - 50, (float)y - 50, (float)z - 50)), std::to_string(i));
	}

	for (int i = 0; i < numObjects; i++) 
	{
		m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix(std::to_string(i)), std::to_string(i));

		spaceOptimzer->PlaceObject(m_pBOMngr->GetBoundingObject(std::to_string(i)));
		//spaceOptimzer->PlaceObject(vector3(0, 0, 0));
	}

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
	

	//m_pBOMngr->Update();//Update collision detection
	
	//m_pBOMngr->DisplaySphere(-1, REWHITE);
	//m_pBOMngr->DisplayReAlligned();
	//m_pBOMngr->DisplayOriented(-1, REWHITE);

	if (showTree)
	{
		spaceOptimzer->DrawAllPartions();
	}

	if (useTree) //spatial optimization
	{
		for (int i = 0; i < numObjects; i++)
		{
			MyBOClass* current = m_pBOMngr->GetBoundingObject(std::to_string(i));
			for (int i3 = 0; i3 < current->currentSpec.size(); i3++)
			{
				if (current->currentSpec[i3]->content.size() > 1)
				{
					for (int i2 = 0; i2 < current->currentSpec[i3]->content.size(); i2++)
					{
						if (current->currentSpec[i3]->content[i2]->name != current->name)
						{
							if (m_pBOMngr->GetBoundingObject(std::to_string(i))->IsColliding(current->currentSpec[i3]->content[i2]) && showCollisions)
							{
								m_pBOMngr->DisplaySphere(std::to_string(i), RERED);
							}
						}
					}
				}
			}
		}
	}
	else
	{
		m_pBOMngr->Update(showCollisions);   //Brute force
	}

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->PrintLine(std::to_string(nFPS), RERED);

	m_pMeshMngr->Print("(F)  Collision Check:");
	if (useTree)
	{
		m_pMeshMngr->PrintLine("Spatial Optimization", REGREEN);
	}
	else
	{
		m_pMeshMngr->PrintLine("Brute Force", RERED);
	}
	m_pMeshMngr->Print("(G)  Show Tree? ");
	if (showTree)
	{
		m_pMeshMngr->PrintLine("True", REGREEN);
	}
	else
	{
		m_pMeshMngr->PrintLine("False", RERED);
	}
	m_pMeshMngr->Print("(H)  Show Collisions? ");
	if (showCollisions)
	{
		m_pMeshMngr->PrintLine("True", REGREEN);
	}
	else
	{
		m_pMeshMngr->PrintLine("False", RERED);
	}
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
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