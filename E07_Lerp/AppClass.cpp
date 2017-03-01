#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Bobadilla, Alberto - 3D Transformations");
	m_v4ClearColor = vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Sets the camera
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 35.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

	srand(time(NULL));
	m_nObjects = rand() % 23 + 5;

	vector3 v3Start = vector3(-m_nObjects, 0.0f, 0.0f);
	vector3 v3End = vector3(m_nObjects, 0.0f, 0.0f);

	m_pSphere = new PrimitiveClass[m_nObjects];
	m_pMatrix = new matrix4[m_nObjects];

	for (int i = 0; i < m_nObjects; i++)
	{
		float fPercent = MapValue(static_cast<float>(i), 0.0f, static_cast<float>(m_nObjects), 0.0f, 1.0f);
		float lerp = v3Start.y + (v3End.y - v3Start.y) * ((fPercent - v3Start.x)/(v3End.x - v3Start.x));
		m_pSphere[i].GenerateSphere(1.0f, 5, vector3(fPercent, 0.0f, 0.0f));
		m_pMatrix[i] = glm::translate(IDENTITY_M4, vector3(lerp, 0.0f, 0.0f));
	}

	//Initializing the primitives
	//m_pSphere->GenerateSphere(0.5f, 5, REWHITE);
}

void AppClass::Update(void)
{
	//This matrices will just place the objects int the right spots
	//m_m4Sphere = glm::translate(IDENTITY_M4, vector3(2.5f, 2.5f, 0.0f));

	for (int i = 0; i < m_nObjects; i++)
	{

	}

	//This matrices will scale them to the right size
	//m_m4Sphere = glm::scale(m_m4Sphere, vector3(2.0f, 2.0f, 2.0f));

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	
	//Matrices from the camera
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	//Renders the meshes using the specified position given by the matrix and in the specified color
	for (int i = 0; i < m_nObjects; i++)
	{
		m_pSphere[i].Render(m4Projection, m4View, m_pMatrix[i]);
	}
	
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_pCube);
	SafeDelete(m_pCone);
	SafeDelete(m_pCylinder);
	SafeDelete(m_pTube);
	SafeDelete(m_pSphere);
	SafeDelete(m_pTorus);
	SafeDelete(m_pMatrix);

	super::Release(); //release the memory of the inherited fields
}