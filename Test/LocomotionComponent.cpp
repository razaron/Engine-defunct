#include "LocomotionComponent.hpp"


LocomotionComponent::LocomotionComponent(float maxVelocity, float maxForce, float mass)
	:maxVel(maxVelocity), maxForce(maxForce), mass(mass)
{
	setType(ComponentType::LOCOMOTION);
}


LocomotionComponent::~LocomotionComponent()
{
}
