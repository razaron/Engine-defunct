#include "TransformComponent.hpp"


TransformComponent::TransformComponent(glm::vec3 position)
	:position(position), scale(1.0f), deepScale(1.0f)
{
	setType(ComponentType::TRANSFORM);
}

TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 scale)
	:position(position), scale(scale), deepScale(1.0f)
{
	setType(ComponentType::TRANSFORM);
}

TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 scale, glm::vec3 deepScale)
	:position(position), scale(scale), deepScale(deepScale)
{
	setType(ComponentType::TRANSFORM);
}


TransformComponent::~TransformComponent()
{
}
