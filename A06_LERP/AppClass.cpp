#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;
	matrix4 travelPoints[11];
	vector3 wayPoint[11];
	int pointTo = 1;
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)
	static DWORD startTimeSystem = GetTickCount();
	DWORD timeApplication = GetTickCount() - startTimeSystem;
	float timer = timeApplication / 1000.0f;
	//cumulative time
	static float fRunTime = 0.0f; //How much time has passed since the program started
#pragma endregion
#pragma region Your Code goes here
	fRunTime += fTimeSpan;
	static int point = 0;
	wayPoint[0] = vector3(-4.0f, -2.0f, 5.0f);
	wayPoint[1] = vector3(1.0f, -2.0f, 5.0f);
	wayPoint[2] = vector3(-3.0f, -1.0f, 3.0f);
	wayPoint[3] = vector3(2.0f, -1.0f, 3.0f);
	wayPoint[4] = vector3(-2.0f, 0.0f, 0.0f);
	wayPoint[5] = vector3(3.0f, 0.0f, 0.0f);
	wayPoint[6] = vector3(-1.0f, 1.0f, -3.0f);
	wayPoint[7] = vector3(4.0f, 1.0f, -3.0f);
	wayPoint[8] = vector3(0.0f, 2.0f, -5.0f);
	wayPoint[9] = vector3(5.0f, 2.0f, -5.0f);
	wayPoint[10] = vector3(1.0f, 3.0f, -5.0f);
	travelPoints[0] = glm::translate(glm::lerp(vector3(-4.0f, -2.0f, 5.0f), vector3(1.0f, -2.0f, 5.0f), fRunTime));
	travelPoints[1] = glm::translate(glm::lerp(vector3(1.0f, -2.0f, 5.0f), vector3(-3.0f, -1.0f, 3.0f), fRunTime));
	travelPoints[2] = glm::translate(glm::lerp(vector3(-3.0f, -1.0f, 3.0f), vector3(2.0f, -1.0f, 3.0f), fRunTime));
	travelPoints[3] = glm::translate(glm::lerp(vector3(2.0f, -1.0f, 3.0f), vector3(-2.0f, 0.0f, 0.0f), fRunTime));
	travelPoints[4] = glm::translate(glm::lerp(vector3(-2.0f, 0.0f, 0.0f), vector3(3.0f, 0.0f, 0.0f), fRunTime));
	travelPoints[5] = glm::translate(glm::lerp(vector3(3.0f, 0.0f, 0.0f), vector3(-1.0f, 1.0f, -3.0f), fRunTime));
	travelPoints[6] = glm::translate(glm::lerp(vector3(-1.0f, 1.0f, -3.0f), vector3(4.0f, 1.0f, -3.0f), fRunTime));
	travelPoints[7] = glm::translate(glm::lerp(vector3(4.0f, 1.0f, -3.0f), vector3(0.0f, 2.0f, -5.0f), fRunTime));
	travelPoints[8] = glm::translate(glm::lerp(vector3(0.0f, 2.0f, -5.0f), vector3(5.0f, 2.0f, -5.0f), fRunTime));
	travelPoints[9] = glm::translate(glm::lerp(vector3(5.0f, 2.0f, -5.0f), vector3(1.0f, 3.0f, -5.0f), fRunTime));
	travelPoints[10] = glm::translate(glm::lerp(vector3(1.0f, 3.0f, -5.0f), vector3(-4.0f, -2.0f, 5.0f), fRunTime));
	travel = travelPoints[point];
	//check the position
	if (fRunTime >= 2)
	{
		point++;
		fRunTime = 0;
		if (point > 10)
		{
			point = 0;
		}
		travel = travelPoints[point];
	}
	m_pMeshMngr->SetModelMatrix(travel, "WallEye");
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
	m_pMeshMngr->Print("\n");
	m_pMeshMngr->PrintLine("Time is: " + std::to_string(timer));
#pragma endregion
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
}