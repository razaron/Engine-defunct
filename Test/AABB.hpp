#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

class AABB
{
public:
	AABB(glm::vec3 position, float radius);
	AABB(glm::vec3 min, glm::vec3 max);
	~AABB();

	void updatePosition(glm::vec3 position);
	bool isCollided(const AABB& aabb);

private:
	glm::vec3 min, max, dimensions;
};

