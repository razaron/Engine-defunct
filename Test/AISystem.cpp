#include "AISystem.hpp"


AISystem::AISystem()
{
	addType("locomotioncomponent");
}


AISystem::~AISystem()
{
}

glm::vec3 truncat(glm::vec3 vector, float max)
{
	float length = glm::length(vector);

	if (length > max)
	{
		return vector / (length / max);
	}

	return vector;
}

void AISystem::update(std::vector<Component*> objects, double delta)
{
	for (auto i : objects)
	{
		process(i);
	}
}

void AISystem::process(Component *object)
{
	SteeringComponent *s = (SteeringComponent*)object->getSubComponent("steeringcomponent");
	TransformComponent *t = (TransformComponent*)object->getSubComponent("transformcomponent");
	LocomotionComponent *l = (LocomotionComponent*)object->getSubComponent("locomotioncomponent");

	glm::vec3 steering;

	if (s && s->getTarget() && t && l)
	{

		switch (s->getBehaviour())
		{
		case Mode::SEEK:
			glm::vec3 dv = glm::normalize(((TransformComponent*)s->getTarget())->getPosition() - t->getPosition()) * l->getMaxVel();
			steering = dv - l->getVelocity();
			steering = truncat(steering, l->getMaxforce());
			steering /= l->getMass();
			break;
		}

		s->setSteering(steering);
	}
}