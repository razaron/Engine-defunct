#include "Frustum.hpp"

Frustum::Frustum()
{
}


Frustum::~Frustum()
{
}

void Frustum::fromMatrix(glm::mat4 &viewProj)
{
	glm::vec3 xaxis = glm::vec3(viewProj[0]);
	glm::vec3 yaxis = glm::vec3(viewProj[1]);
	glm::vec3 zaxis = glm::vec3(viewProj[2]);
	glm::vec3 waxis = glm::vec3(viewProj[3]);

	planes[0] = Plane(waxis - xaxis, viewProj[3][3] - viewProj[0][3], true);
	planes[1] = Plane(waxis + xaxis, viewProj[3][3] + viewProj[0][3], true);
	planes[2] = Plane(waxis - yaxis, viewProj[3][3] - viewProj[1][3], true);
	planes[3] = Plane(waxis + yaxis, viewProj[3][3] + viewProj[1][3], true);
	planes[4] = Plane(waxis - zaxis, viewProj[3][3] - viewProj[2][3], true);
	planes[5] = Plane(waxis + zaxis, viewProj[3][3] + viewProj[2][3], true);
}

bool Frustum::insideFrustum(SceneNode *n)
{
	for (int i = 0; i < 6; ++i)
	{
		if (!planes[i].sphereInPlane(glm::vec3(n->getWorldTransform()[3]), n->getBoundingRadius()))
			return false;
	}

	return true;
}