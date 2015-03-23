#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

class Plane
{
public:
	Plane(){};
	Plane(glm::vec3 normal, float distance, bool normalise=false);
	~Plane();

	glm::vec3 getNormal(){ return normal; };
	void setNormal(glm::vec3 normal){ this->normal = normal; };

	float getDistance(){ return distance; };
	void setDistance(float distance){ this->distance = distance; };

	bool sphereInPlane(glm::vec3 position, float radius);

private:
	glm::vec3 normal;
	float distance;
};

