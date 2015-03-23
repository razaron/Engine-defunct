#include "Plane.hpp"


Plane::Plane(glm::vec3 normal, float distance, bool normalise)
{
	if (normalise)
	{
		float length = std::sqrt(glm::dot(normal, normal));
		this->normal = normal / length;
		this->distance = distance / length;
	}
	else
	{
		this->normal = normal;
		this->distance = distance;
	}
}


Plane::~Plane()
{
}

bool Plane::sphereInPlane(glm::vec3 position, float radius)
{
	if (glm::dot(position, normal) + distance <= -radius)
		return false;
	
	return true;
}