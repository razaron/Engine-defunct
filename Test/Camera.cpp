#include "Camera.hpp"


Camera::Camera(glm::vec3 position, glm::vec3 target)
	:position(position), target(target)
{
}


Camera::~Camera()
{
}

void Camera::translate(glm::vec3 vector)
{
	position + vector;
}