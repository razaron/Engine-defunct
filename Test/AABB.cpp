#include "AABB.hpp"


AABB::AABB(glm::vec3 position, float radius)
	:dimensions(glm::vec3(radius))
{
	min = position - dimensions;
	max = position + dimensions;
}

AABB::AABB(glm::vec3 min, glm::vec3 max)
	:min(min), max(max), dimensions(max-min)
{
}

AABB::~AABB()
{
}

void AABB::updatePosition(glm::vec3 position)
{
	min = position - dimensions;
	max = position + dimensions;
}

bool AABB::isCollided(const AABB& b)
{
	if (max.x > b.min.x && max.y > b.min.y && max.y > b.min.y && min.x < b.max.x && min.y < b.max.y && min.z < b.max.z)
		return true;

	return false;
}