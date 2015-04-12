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

	float getBoundingRadius(){ return boundingRadius; };
	void setBoundingRadius(float boundingRadius){ this->boundingRadius = boundingRadius; };

	ColliderComponent* getCollidingWith(){ return collidingWith; };
	void setCollidingWith(ColliderComponent *collidingWith){ this->collidingWith = collidingWith; };

	bool getIsTrigger(){ return isTrigger; };
	void setIsTrigger(bool isTrigger){ this->isTrigger = isTrigger; };

private:
	AABB aabb;
	float boundingRadius;
	bool isTrigger;

	ColliderComponent *collidingWith;
};

