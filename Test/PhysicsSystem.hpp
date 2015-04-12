#pragma once
#include "System.hpp"
#include "ColliderComponent.hpp"
#include "TransformComponent.hpp"
#include "SteeringComponent.hpp"
#include "LocomotionComponent.hpp"

class PhysicsSystem :
	public System
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	virtual void update(std::vector<Component*> gameobjects, double delta) override;
	virtual void process(Component *component) override;
	//void processSubComponents(Component *c, SceneNode *n);

private:
	double elapsed;
};

