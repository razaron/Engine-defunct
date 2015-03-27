#pragma once
#include "System.hpp"
#include "TransformComponent.hpp"
#include "SteeringComponent.hpp"
#include "LocomotionComponent.hpp"

class AISystem :
	public System
{
public:
	AISystem();
	~AISystem();

	virtual void update(std::vector<Component*> gameobjects, double delta) override;
	virtual void process(Component *component) override;
};

