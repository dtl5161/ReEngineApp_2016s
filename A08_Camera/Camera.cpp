#include "Camera.h"
//get view

Camera::Camera(){
	m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);;
	m_m4Orthographic = glm::ortho(-10.0f, 10.0f, -5.0f, 5.0f, 0.01f, 1000.0f);
	m_m4View = matrix4();
}

Camera::~Camera() {
	//
}

matrix4 Camera::GetView() {
	return m_m4View;
}
//get either projection or orthographic view
matrix4 Camera::GetProjection(bool bOrthographic) {
	if (bOrthographic == true) {
		return m_m4Orthographic;
	}
	else {
		return m_m4Projection;
	}
}
//set the camera's position
void Camera::SetPosition(vector3 v3Position) {
	/*matrix4 tempPosition = m_m4View;
	vector3 temp = vector3(m_m4View[3][0], m_m4View[3][1], m_m4View[3][2]);
	m_m4View[3][0] = 0.0f;
	m_m4View[3][1] = 0.0f;
	m_m4View[3][2] = 0.0f;*/
	m_m4View = glm::translate(m_m4View,v3Position);
}
//set the camera's target
void Camera::SetTarget(vector3 v3Target) {
	matrix4 tempPosition = m_m4Projection;
	m_m4Projection = glm::translate(IDENTITY_M4, v3Target);
}

//set the camera's Up vector
void Camera::SetUp(vector3 v3Up) {
	quaternion upQuat = quaternion(v3Up);
	matrix4 tempPosition = m_m4View;
	vector3 temp = vector3(m_m4View[3][0], m_m4View[3][1], m_m4View[3][2]);
	m_m4View[3][0] = 0.0f;
	m_m4View[3][1] = 0.0f;
	m_m4View[3][2] = 0.0f;
	m_m4View = glm::translate(IDENTITY_M4, temp);
	m_m4View = m_m4View * ToMatrix4(upQuat);
}

//move the camera forward
void Camera::MoveForward(float fIncrement) {
	SetPosition(vector3(0.0f,0.0f,fIncrement));
}

//move the camera sideways
void Camera::MoveSideways(float fIncrement) {
	SetPosition(vector3(fIncrement, 0.0f, 0.0f));
}

//move the camera vertically
void Camera::MoveVertical(float fIncrement) {
	SetPosition(vector3(0.0f, fIncrement, 0.0f));
}

//change the camera's pitch
void Camera::ChangePitch(float fIncrement) {
	quaternion rot = glm::angleAxis(-fIncrement,vector3(1.0f,0.0f,0.0f));
	m_m4Projection = m_m4Projection * ToMatrix4(rot);
}

//change the camera's roll
void Camera::ChangeRoll(float fIncrement) {
	quaternion rot = glm::angleAxis(-fIncrement, vector3(0.0f, 0.0f, 1.0f));
	m_m4Projection = m_m4Projection * ToMatrix4(rot);
}

//change the camera's yaw
void Camera::ChangeYaw(float fIncrement) {
	quaternion rot = glm::angleAxis(-fIncrement, vector3(0.0f, 1.0f, 0.0f));
	m_m4Projection = m_m4Projection * ToMatrix4(rot);
}

