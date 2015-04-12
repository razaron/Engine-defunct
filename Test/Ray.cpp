#include "Ray.hpp"


Ray::Ray(glm::vec3 p1, glm::vec3 p2)
{
	pos = p1;
	dir = glm::normalize(p2 - p1);
	length = glm::length(p2 - p1);
}


Ray::~Ray()
{
}
