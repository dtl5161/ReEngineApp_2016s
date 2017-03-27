#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - YOUR USER NAME GOES HERE"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);

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
		CameraRotation();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

	//Earth Orbit
	double fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route

	//setting up quats
	glm::quat earthQuat1 = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	glm::quat earthQuat2 = glm::quat(vector3(0.0f, 359.0f, 0.0f));
	glm::quat moonQuat1 = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	glm::quat moonQuat2 = glm::quat(vector3(0.0f, -359.0f, 0.0f));

	//slerp
	

	//mat4s
	matrix4 m4Earth = glm::toMat4(glm::mix(earthQuat1, earthQuat2, (float)fRunTime / 10));
	matrix4 step1 = glm::translate(vector3(11.0f,0.0f,0.0f));
	matrix4 earthPos = m4Earth * step1;
	matrix4 m4Moon = earthPos;
	matrix4 step2 = glm::translate(vector3(2.0f, 0.0f, 0.0f));
	matrix4 m4Moon2 = glm::toMat4(glm::mix(earthQuat1, earthQuat2, (float)fRunTime / 5));
	//m4Moon = m4Moon * m4Earth;
	matrix4 moonPos = m4Moon * m4Moon2 * step2;
	//Setting the matrices
	m_pMeshMngr->SetModelMatrix(IDENTITY_M4, "Sun");
	m_pMeshMngr->SetModelMatrix(earthPos, "Earth");
	m_pMeshMngr->SetModelMatrix(moonPos, "Moon");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	static int nEarthOrbits = 0;
	static int nEarthRevolutions = 0;
	static int nMoonOrbits = 0;
	double check = fRunTime;
	static int tick1 = 1;
	static int tick2 = 1;
	static int tick3 = 1;
	if(check/(12*tick1) >= 1)
	{
		nEarthOrbits++;
		tick1++;
	}
	if (check / (0.033 * tick2) >= 1)
	{
		nEarthRevolutions++;
		tick2++;
	}
	if (check / (5.5 * tick3) >= 1)
	{
		nMoonOrbits++;
		tick3++;
	}

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

	//Render the grid based on the camera's mode:
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
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}