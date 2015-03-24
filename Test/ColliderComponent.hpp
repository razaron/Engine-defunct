#pragma once
#include "Component.hpp"
#include "AABB.hpp"

class ColliderComponent :
	public Component
{
public:
	ColliderComponent(glm::vec3 position,  float radius);
	~ColliderComponent();

	AABB* getAABB(){ return &aabb; };
	void setAABB(const AABB &aabb){ this->aabb = aabb; };

	ColliderComponent* getCollidingWith(){ return collidingWith; };
	void setCollidingWith(ColliderComponent *collidingWith){ this->collidingWith = collidingWith; };

private:
	AABB aabb;
	ColliderComponent *collidingWith;
};

