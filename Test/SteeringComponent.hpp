#pragma once
#include "Component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

typedef struct behaviour Behaviour;

enum class Mode{SEEK, FLEE, ARRIVE, AVOID};

struct behaviour
{
	Mode mode;
	std::vector<Component*> targets;
	float weight = 1.0f;
};

class SteeringComponent :
	public Component
{
public:
	SteeringComponent();
	~SteeringComponent();

	std::vector<Behaviour*> getBehaviours(){ return behaviours; };
	void addBehaviour(Behaviour *behaviour){ behaviours.push_back(behaviour); };
	Behaviour* getBehaviour(Mode behaviour){ for (auto i : behaviours) { if (i->mode == behaviour)return i; }return nullptr; };
	void setSteering(glm::vec3 steering){ this->steering = steering; };
	glm::vec3 getSteering(){ return steering; };

private:
	std::vector<Behaviour*> behaviours;
	glm::vec3 steering;
};

