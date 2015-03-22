#include "RenderComponent.hpp"


RenderComponent::RenderComponent()
{
	setType("rendercomponent");
}

RenderComponent::RenderComponent(glm::vec3 position, glm::vec3 scale)
{
	setType("rendercomponent");

	addComponent(new TransformComponent(position, scale));
}

RenderComponent::RenderComponent(glm::vec3 position, glm::vec3 scale, MeshComponent *mesh)
{
	setType("rendercomponent");

	addComponent(new TransformComponent(position, scale));
	addComponent(mesh);
}


RenderComponent::~RenderComponent()
{
}
