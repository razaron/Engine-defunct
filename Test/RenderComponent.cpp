#include "RenderComponent.hpp"


RenderComponent::RenderComponent()
	:ovColour(glm::vec3(1.0f)), alpha(1.0f)
{
	setType(ComponentType::RENDER);
}

RenderComponent::RenderComponent(glm::vec3 position, glm::vec3 scale)
	: ovColour(glm::vec3(1.0f)), alpha(1.0f)
{
	setType(ComponentType::RENDER);

	addComponent(new TransformComponent(position, scale));
}

RenderComponent::RenderComponent(glm::vec3 position, glm::vec3 scale, MeshComponent *mesh)
	:ovColour(glm::vec3(1.0f)), alpha(1.0f)
{
	setType(ComponentType::RENDER);

	addComponent(new TransformComponent(position, scale));
	addComponent(mesh);
}


RenderComponent::~RenderComponent()
{
}
