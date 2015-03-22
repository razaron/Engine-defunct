#include "RenderComponent.hpp"


RenderComponent::RenderComponent()
	:rotation(0.0f)
{
	setType("rendercomponent");
}

RenderComponent::RenderComponent(glm::vec3 position, glm::vec3 scale)
	:rotation(0.0f)
{
	setType("rendercomponent");

	addComponent(new TransformComponent(position, scale));
}

RenderComponent::RenderComponent(glm::vec3 position, glm::vec3 scale, MeshComponent *mesh)
	:rotation(0.0f)
{
	setType("rendercomponent");

	addComponent(new TransformComponent(position, scale));
	addComponent(mesh);
}


RenderComponent::~RenderComponent()
{
}
