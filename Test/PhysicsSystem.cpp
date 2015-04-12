#include "PhysicsSystem.hpp"


PhysicsSystem::PhysicsSystem()
	:elapsed(0.0f)
{
}


PhysicsSystem::~PhysicsSystem()
{
}

glm::vec3 truncate(glm::vec3 vector, float max)
{
	float length = glm::length(vector);
	
	if (length > max)
	{
		return vector / (length / max);
	}

	return vector;
}

void PhysicsSystem::update(std::vector<Component*> gameobjects, double delta)
{
	elapsed += delta;
	while (elapsed >= 0.01f)
	{
		for (auto i : gameobjects)
		{
			ColliderComponent *a = (ColliderComponent *)i->getSubComponent("collidercomponent");
			TransformComponent *t = (TransformComponent *)i->getSubComponent("transformcomponent");


			AABB prev = *a->getAABB();
			process(i);

			//Update what it is colliding with now
			if (a)
			{
				for (auto j : gameobjects)
				{
					ColliderComponent *b = (ColliderComponent *)j->getSubComponent("collidercomponent");

					if (i != j && b && a->getAABB()->isCollided(*b->getAABB()))
					{
						a->setCollidingWith(b);
						std::cout << a->getHandle() << " hit " << b->getHandle() << std::endl;
					}
				}

				if (a->getCollidingWith() && !a->getCollidingWith()->getIsTrigger())
				{
					t->setPosition(t->getPosition() - a->getAABB()->minSeparation(*a->getCollidingWith()->getAABB()));
					a->getAABB()->updatePosition(t->getPosition());
				}
			}
		}
		elapsed -= 0.01f;
	}
	
}

void PhysicsSystem::process(Component *component)
{
	ColliderComponent *a = (ColliderComponent *)component->getSubComponent("collidercomponent");
	TransformComponent *t = (TransformComponent *)component->getSubComponent("transformcomponent");
	SteeringComponent *s = (SteeringComponent*)component->getSubComponent("steeringcomponent");
	LocomotionComponent *l = (LocomotionComponent*)component->getSubComponent("locomotioncomponent");

	//Update gameobjects ColliderComponent
	if (t)
		a->getAABB()->updatePosition(t->getPosition());

	//Check if still colliding with previous collidee
	if (a->getCollidingWith() && !a->getAABB()->isCollided(*a->getCollidingWith()->getAABB()))
		a->setCollidingWith(nullptr);

	//Update position based on steering forces and locomotion
	if (s && t && l)
	{
		l->setVelocity(truncate(l->getVelocity() + s->getSteering(), l->getMaxVel()));
		t->setPosition(t->getPosition() + (l->getVelocity()*(0.01f)));
		a->getAABB()->updatePosition(t->getPosition());
	}
}
