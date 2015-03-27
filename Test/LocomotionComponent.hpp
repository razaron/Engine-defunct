#pragma once
#include "Component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

class LocomotionComponent :
	public Component
{
public:
	LocomotionComponent(float maxVelocity, float maxForce, float mass);
	~LocomotionComponent();

	void setVelocity(glm::vec3 velocity){ this->velocity = velocity; };
	glm::vec3 getVelocity(){ return velocity; };
	void setMaxVel(float maxVel){ this->maxVel = maxVel; };
	float getMaxVel(){ return maxVel; };
	void setMaxForce(float maxForce){ this->maxForce = maxForce; };
	float getMaxforce(){ return maxForce; };
	void setMass(float mass){ this->mass = mass; };
	float getMass(){ return mass; };

private:
	glm::vec3 velocity;
	float maxVel, maxForce, mass;
};

