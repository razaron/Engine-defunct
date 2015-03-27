#include "ColliderComponent.hpp"


ColliderComponent::ColliderComponent(glm::vec3 position, float radius)
	:aabb(AABB(position, radius)), boundingRadius(radius), isTrigger(false), collidingWith(nullptr)
{
	setType("collidercomponent");
}


ColliderComponent::~ColliderComponent()
{
}
