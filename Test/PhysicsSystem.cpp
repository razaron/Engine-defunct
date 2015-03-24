#include "PhysicsSystem.hpp"


PhysicsSystem::PhysicsSystem()
{
}


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::update(std::vector<Component*> gameobjects)
{
	for (auto i : gameobjects)
	{
		ColliderComponent *a = (ColliderComponent *)i->getSubComponent("collidercomponent");
		TransformComponent *t = (TransformComponent *)i->getSubComponent("transformcomponent");

		if (t)
			a->getAABB()->updatePosition(t->getPosition());

		if (a->getCollidingWith() && !a->getAABB()->isCollided(*a->getCollidingWith()->getAABB()))
			a->setCollidingWith(nullptr);

		if (a)
		{
			for (auto j : gameobjects)
			{
				ColliderComponent *b = (ColliderComponent *)j->getSubComponent("collidercomponent");

				if (i != j && b && a->getAABB()->isCollided(*b->getAABB()))
					a->setCollidingWith(b);
			}
		}		
	}
}

void PhysicsSystem::process(Component *component)
{

}
