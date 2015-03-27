#include "Camera.hpp"


Camera::Camera(glm::vec3 position, glm::vec3 target)
	:position(position), target(target), zoom(75.0f)
{
}


Camera::~Camera()
{
}