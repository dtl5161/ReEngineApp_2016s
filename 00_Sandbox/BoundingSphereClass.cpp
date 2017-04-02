#include "BoundingSphereClass.h"

BoundingSphereClass::BoundingSphereClass(std::vector<vector3> vertexList)
{
	m_fRadius = 0.0f;
	m_v3Center = vector3(0.0);

	if (vertexList.size() == 0) return;

	vector3 v3Min = vertexList[0];
	vector3 v3Max = vertexList[0];
	for (int i = 0; i < vertexList.size(); i++)
	{
		//checking for x
		if (v3Min.x > vertexList[i].x)
		{
			v3Min.x = vertexList[i].x;
		}
		else if (v3Max.x > vertexList[i].x)
		{
			v3Max.x = vertexList[i].x;
		}

		//checking for y
		if (v3Min.y > vertexList[i].y)
		{
			v3Min.y = vertexList[i].y;
		}
		else if (v3Max.y > vertexList[i].y)
		{
			v3Max.y = vertexList[i].y;
		}

		//checking for z
		if (v3Min.z > vertexList[i].z)
		{
			v3Min.z = vertexList[i].z;
		}
		else if (v3Max.z > vertexList[i].z)
		{
			v3Max.z = vertexList[i].z;
		}
	}

	m_v3Center = (v3Max + v3Min) / 2.0f;
	for (int i = 0; i < vertexList.size(); i++)
	{
		float distance = glm::distance(m_v3Center, vertexList[i]);
		if (distance > m_fRadius)
		{
			m_fRadius = distance;
		}
	}
}
bool BoundingSphereClass::isColliding(BoundingSphereClass other)
{
	return true;
}