#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	static float fTimer = 0.0f;//creates a timer
	static uint uClock = m_pSystem->GenClock();//ask the system for a new clock id
	float fDeltaTime = m_pSystem->LapClock(uClock);//lap the selected clock
	fTimer += fDeltaTime;//add the delta time to the current clock
#pragma endregion

#pragma region YOUR CODE GOES HERE
	static bool topReached = false;
	static float time = 0.0f;
	modelMatrix = IDENTITY_M4;
	glm::quat q1 = glm::angleAxis(0.0f, vector3(0.0f, 0.0f, 1.0f));
	quaternion q2 = glm::angleAxis(150.0f, vector3(0.0f, 0.0f, 1.0f));
	vector3 v1 = vector3(0.0f, 0.0f, 0.0f);
	vector3 v2 = vector3(0.0f, 3.0f, 0.0f);
	vector3 v3;
	vector3 v4;
	quaternion q3;
	matrix4 check;
	matrix4 step1;
	matrix4 step2;
	q3 = glm::mix(q1, q2, fTimer);
	step1 = glm::translate(glm::lerp(v1, v2, fTimer / 2.5f));
	check = ToMatrix4(q3) * step1;

	time += fDeltaTime;
	if (fTimer >= 2.5) {
		fTimer = 0.0;
	}
	modelMatrix = check;
#pragma endregion

#pragma region DOES NOT NEED CHANGES
	m_pMeshMngr->SetModelMatrix(modelMatrix, 0);//Set the model matrix to the model

	m_pMeshMngr->AddSkyboxToRenderList();//Adds a skybox to the renderlist
	m_pMeshMngr->AddInstanceToRenderList("ALL"); //Adds all loaded instances to the render list

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->PrintLine("Timer: ");
	m_pMeshMngr->PrintLine(std::to_string(time), REGREEN);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

