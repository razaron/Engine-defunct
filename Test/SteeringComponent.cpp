#include "SteeringComponent.hpp"


SteeringComponent::SteeringComponent(Mode behaviour)
	:behaviour(behaviour), target(nullptr)
{
	setType("steeringcomponent");
}


SteeringComponent::~SteeringComponent()
{
}
