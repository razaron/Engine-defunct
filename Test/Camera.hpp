#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target);
	virtual ~Camera();
	
	glm::vec3 getPosition(){ return position; };
	glm::vec3 getTarget(){ return target; };
	void setPosition(glm::vec3 position){ this->position = position; };
	void setTarget(glm::vec3 target){ this->target = target; };

	glm::mat4 getView(){ return glm::lookAt(position, target, glm::vec3(0.0f, 0.0f, 1.0f)); };

	float getZoom(){ return zoom; };
	void setZoom(float zoom){ this->zoom = zoom; };
	void translate(glm::vec3 vector){ position += vector; };

private:
	glm::vec3 position, target;
	float zoom;
};

