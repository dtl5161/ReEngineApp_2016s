#pragma once

#include "RE\ReEng.h"

class BoundingSphereClass
{
public:
	float m_fRadius = 0.0f;
	vector3 m_v3Center = vector3(0.0);

public:
	BoundingSphereClass(std::vector<vector3> vertexList);
	bool isColliding(BoundingSphereClass other);
};
