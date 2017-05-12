#pragma once
#include "RE\ReEng.h"

class BoundingSphereClass
{
public:
	float m_fRadius = 0.0f; //radius of the sphere
	vector3 m_v3CenterLocal = vector3(0.0f); //center of the sphere in local space
	vector3 m_v3CenterGlobal = vector3(0.0f); //center of the sphere in global space
	vector3 m_v3Size;
	matrix4 m_m4ToWorld = IDENTITY_M4; //matrix that takes you from local to global space
	MeshManagerSingleton* m_pMeshMngr = nullptr; //for drawing the sphere

	bool m_bColliding = false;
	/*
	Constructor, needs a vertex list
	*/
	BoundingSphereClass(std::vector<vector3> vertexList);
	/*
	Renders the sphere based on the radius and the center in global space
	*/
	void RenderSphere();
	/*
	Sets the transform from the local to world matrix
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);

	/*
	Will check the collision with another object
	*/
	bool IsColliding(BoundingSphereClass* a_other);
};