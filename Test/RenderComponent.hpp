#pragma once

#include "Component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

class RenderComponent: public Component
{
public:
	RenderComponent(glm::vec3 position, glm::vec3 scale);
	~RenderComponent();

	glm::vec3 getPosition(){ return position; };
	glm::vec3 getScale(){ return scale; };
	glm::mat4 getTransform(){ return glm::translate(position) * glm::scale(scale); };
	void setPosition(glm::vec3 position){ this->position = position; };


	float getRotation(){ return rotation; };
	void setRotation(float angle){ rotation = angle; };

private:
	glm::vec3 position, scale;
	float rotation;
};

