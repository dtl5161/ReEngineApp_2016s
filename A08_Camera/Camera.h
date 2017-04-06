#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
//#include <chrono>

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class Camera
{
	//variables

	matrix4 m_m4Projection;
	matrix4 m_m4Orthographic;
	matrix4 m_m4View;
public:
	Camera();
	~Camera();
	//get view
	matrix4 GetView();

	//get either projection or orthographic view
	matrix4 GetProjection(bool bOrthographic);

	//
	void SetPosition(vector3 v3Position);

	//
	void SetTarget(vector3 v3Target);

	//
	void SetUp(vector3 v3Up);

	//
	void MoveForward(float fIncrement);

	//
	void MoveSideways(float fIncrement);

	//
	void MoveVertical(float fIncrement);

	//
	void ChangePitch(float fIncrement);

	//
	void ChangeRoll(float fIncrement);

	//
	void ChangeYaw(float fIncrement);


};

#endif //__CAMERA_H_