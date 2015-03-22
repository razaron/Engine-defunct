#pragma once
#include "Component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

class TransformComponent : public Component
{
public:
	TransformComponent(glm::vec3 position);
	TransformComponent(glm::vec3 position, glm::vec3 scale);
	TransformComponent(glm::vec3 position, glm::vec3 scale, glm::vec3 deepScale);
	~TransformComponent();

	glm::vec3 getPosition(){ return position; };
	glm::vec3 getScale(){ return scale; };
	glm::mat4 getTransform(){ return glm::translate(position) * glm::scale(deepScale); };
	void setPosition(glm::vec3 position){ this->position = position; };
	void setScale(glm::vec3 scale){ this->scale = scale; };
	void setDeepScale(glm::vec3 deepScale){ this->deepScale = deepScale; };

private:
	glm::vec3 position, scale, deepScale;
};

