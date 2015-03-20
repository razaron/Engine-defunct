#include "RenderComponent.hpp"


RenderComponent::RenderComponent(glm::vec3 position, glm::vec3 scale)
	:position(position), scale(scale), rotation(0.0f)
{
	setType("rendercomponent");
}


RenderComponent::~RenderComponent()
{
}
