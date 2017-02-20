#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("3D Shapes"); // Window Name
}

void AppClass::InitVariables(void)
{
	//Reserve Memory for a MyMeshClass object
	m_pPrimitive = new MyPrimitive();
	m_pPrimitive->GenerateCube(1.0f, REWHITE);
	m_pPrimitive->GenerateCone(1.0f, 1.0f, 12, REGREEN);
	m_pPrimitive->GenerateCylinder(1.0f, 2.0f, 7, REBLUE);
	m_pPrimitive->GenerateTube(1.0f, 0.7f, 2.0f, 7, REBROWN);
	m_pPrimitive->GenerateSphere(1.0f, 3, RERED);

	m_pCube = new MyPrimitive();
	m_pCone = new MyPrimitive();
	m_pCylinder = new MyPrimitive();
	m_pTube = new MyPrimitive();
	m_pSphere = new MyPrimitive();

	//Initializing the primitives
	m_pSphere->GenerateSphere(0.5f, 5, REWHITE);
	m_pCone->GenerateCone(0.5f, 0.5f, 10, REGREEN);
	m_pCylinder->GenerateCylinder(0.5f, 0.5f, 10, REBLUE);
	m_pTube->GenerateTube(0.5f, 0.25f, 0.5f, 10, REBROWN);
	m_pCube->GenerateCube(0.5f, RERED);
}

void AppClass::Update(void)
{
	m_m4Sphere = glm::translate(IDENTITY_M4, vector3(2.5f, 2.5f, 0.0f));
	m_m4Cone = glm::translate(IDENTITY_M4, vector3(0.0f, 2.0f, 0.0f));
	m_m4Cylinder = glm::translate(IDENTITY_M4, vector3(-2.0f, 0.0f, 0.0f));
	m_m4Tube = glm::translate(IDENTITY_M4, vector3(0.0f, -2.0f, 0.0f));
	m_m4Cube = glm::translate(IDENTITY_M4, vector3(2.0f, 0.0f, 0.0f));

	//This matrices will scale them to the right size
	m_m4Sphere = glm::scale(m_m4Sphere, vector3(2.0f, 2.0f, 2.0f));
	//m_m4Cone = glm::scale(m_m4Cone, vector3(2.0f, 2.0f, 2.0f));
	m_m4Cylinder = glm::scale(m_m4Cylinder, vector3(2.0f, 2.0f, 2.0f));
	m_m4Tube = glm::scale(m_m4Tube, vector3(2.0f, 2.0f, 2.0f));
	m_m4Cube = glm::scale(m_m4Cube, vector3(2.0f, 2.0f, 2.0f));

	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	m_pPrimitive->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), ToMatrix4(m_qArcBall));
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	//Render the grid based on the camera's mode:
	m_pSphere->Render(m4Projection, m4View, m_m4Sphere);
	m_pCone->Render(m4Projection, m4View, m_m4Cone);
	m_pCylinder->Render(m4Projection, m4View, m_m4Cylinder);
	m_pTube->Render(m4Projection, m4View, m_m4Tube);
	m_pCube->Render(m4Projection, m4View, m_m4Cube);
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_pPrimitive); //Release the shape
	SafeDelete(m_pCube);
	SafeDelete(m_pCone);
	SafeDelete(m_pCylinder);
	SafeDelete(m_pTube);
	SafeDelete(m_pSphere);
	super::Release(); //release the memory of the inherited fields
}