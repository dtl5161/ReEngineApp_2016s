#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Paradox Billiards");
}

void AppClass::InitVariables(void)
{
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 10.0f, 56.0f),//Camera position
		vector3(0.0f, 0.0f, 0.0f),//What Im looking at
		REAXISY);//What is up
	//Load a model onto the Mesh manager
	m_pMeshMngr->LoadModel("media\\models\\table_with_colors.obj", "table1");
	m_pMeshMngr->LoadModel("media\\models\\table_with_colors.obj", "table2");
	m_pMeshMngr->LoadModel("media\\models\\table_with_colors.obj", "table3");
	m_pMeshMngr->LoadModel("media\\models\\table_with_colors.obj", "table4");

	m_boMngr = BoundingObjectManager::GetInstance();

	m_backgroundOn = false;
	m_seeControls = true;
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

	//Call the arcball method
	ArcBall();

	//Object Movement
	float stretch = 9.0f;
	static float fTimer = 0.0f;
	static int nClock = m_pSystem->GenClock();
	float fDeltaTime = static_cast<float>(m_pSystem->LapClock(nClock));
	fTimer += fDeltaTime;

	static quaternion table1Rot = quaternion(vector3(0.0f, -PI / 2.0f, 0.0f));
	static quaternion table2Rot = quaternion(vector3(PI, -PI / 2.0f, 0.0f));
	static quaternion table3Rot = quaternion(vector3(0.0f, PI / 2.0f, PI / 2.0f));
	static quaternion table4Rot = quaternion(vector3(0.0f, PI / 2.0f, -PI / 2.0f));

	static vector3 table3Pos = vector3(stretch, 0.0, 0.0); //right
	static vector3 table4Pos = vector3(-stretch, 0.0, 0.0); //left
	static vector3 table2Pos = vector3(0.0, stretch, 0.0); //up
	static vector3 table1Pos = vector3(0.0, -stretch, 0.0); //down

	//set the translate to create the transform matrix
	//matrix4 m4Transform = glm::translate(m_v3Position) * ToMatrix4(m_qArcBall);
	m_pMeshMngr->SetModelMatrix(glm::translate(ToMatrix4(m_sceneRotation), table1Pos) * ToMatrix4(table1Rot) * ToMatrix4(m_tableRotation), "table1");
	m_pMeshMngr->SetModelMatrix(glm::translate(ToMatrix4(m_sceneRotation), table2Pos) * ToMatrix4(table2Rot) * ToMatrix4(m_tableRotation), "table2");
	m_pMeshMngr->SetModelMatrix(glm::translate(ToMatrix4(m_sceneRotation), table3Pos) * ToMatrix4(table3Rot) * ToMatrix4(m_tableRotation), "table3");
	m_pMeshMngr->SetModelMatrix(glm::translate(ToMatrix4(m_sceneRotation), table4Pos) * ToMatrix4(table4Rot) * ToMatrix4(m_tableRotation), "table4");
	

	//Adds all loaded instance to the render list
	if (!m_backgroundOn)
	{
		m_pMeshMngr->AddSkyboxToRenderList();
	}
	else
	{
		m_pMeshMngr->AddSkyboxToRenderList("barPh5.png");
	}
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	m_pMeshMngr->PrintLine("");//Add a line on top
	if (m_seeControls)
	{
		m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	
		m_pMeshMngr->Print("I,O,P: Rotate tables");
		m_pMeshMngr->Print(" - J,K,L: Rotation Chaos");
		m_pMeshMngr->Print("\nW, A, S, D: Move camera");
		m_pMeshMngr->Print("\nQ, E: Move camera vertically");
		m_pMeshMngr->Print("\nRight click: Aim camera");
		m_pMeshMngr->Print("\nR: Reset tables");
		m_pMeshMngr->Print("\nB: Toggle background");
		m_pMeshMngr->Print("\nT: Toggle controls");
	}
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	//m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	//SafeDelete(m_pBS0);
	//SafeDelete(m_pBS1);
	//SafeDelete(m_pBS2);
	super::Release(); //release the memory of the inherited fields
	m_boMngr->ReleaseInstance();
}