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

glm::vec3 AABB::minSeparation(const AABB& aabb)
{
	float dx = 0, dy = 0, dz = 0;

	glm::vec3 a = aabb.min - max;
	glm::vec3 b = aabb.max - min;

	a=glm::abs(a);
	b=glm::abs(b);

	if (a.x < b.x)
		dx = a.x;
	else
		dx = b.x;

	if (a.y < b.y)
		dy = a.y;
	else
		dy = b.y;

	if (a.z < b.z)
		dz = a.z;
	else
		dz = b.z;

	if (dx < dy && dx < dz)
	{
		dy = 0.0f;
		dz = 0.0f;
	}
	if (dy < dx && dy < dz)
	{
		dx = 0.0f;
		dz = 0.0f;
	}

	if (dz < dy && dz < dx)
	{
		dx = 0.0f;
		dy = 0.0f;
	}

	return glm::vec3(dx, dy, dz);
}