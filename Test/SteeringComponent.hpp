#pragma once
#include "Component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

enum class Mode{SEEK};

class SteeringComponent :
	public Component
{
public:
	SteeringComponent(Mode behaviour);
	~SteeringComponent();

	void setTarget(Component *target){ this->target = target; };
	Component* getTarget(){ return target; };
	void setBehaviour(Mode behaviour){ this->behaviour = behaviour; };
	Mode getBehaviour(){ return behaviour; };
	void setSteering(glm::vec3 steering){ this->steering = steering; };
	glm::vec3 getSteering(){ return steering; };

private:
	Mode behaviour;
	Component *target;
	glm::vec3 steering;
};

