#pragma once

//#define GLM_FORCE_PURE
#include "Plane.hpp"
#include "SceneNode.hpp"


class Frustum
{
public:
	Frustum();
	~Frustum();

	void fromMatrix(glm::mat4 &viewProj);
	bool insideFrustum(SceneNode *n);

private:
	Plane planes[6];
};

