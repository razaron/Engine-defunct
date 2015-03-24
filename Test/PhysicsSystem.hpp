#pragma once
#include "System.hpp"
#include "ColliderComponent.hpp"
#include "TransformComponent.hpp"

class PhysicsSystem :
	public System
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	virtual void update(std::vector<Component*> gameobjects) override;
	virtual void process(Component *component) override;
	//void processSubComponents(Component *c, SceneNode *n);

private:

};

