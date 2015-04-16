#include "AISystem.hpp"


AISystem::AISystem()
{
	addType(ComponentType::LOCOMOTION);
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

Component* isObstacle(Component *object, Component *target)
{
	TransformComponent *t = (TransformComponent*)object->getSubComponent(ComponentType::TRANSFORM);
	LocomotionComponent *l = (LocomotionComponent*)object->getSubComponent(ComponentType::LOCOMOTION);

	TransformComponent *tt = (TransformComponent*)target->getSubComponent(ComponentType::TRANSFORM);
	ColliderComponent *tc = (ColliderComponent *)target->getSubComponent(ComponentType::COLLIDER);

	float dLength = (glm::length(l->getVelocity()) / l->getMaxVel()) *5.0f;
	glm::vec3 ahead = t->getPosition() + (glm::normalize(l->getVelocity())*dLength);
	glm::vec3 ahead2 = t->getPosition() + (glm::normalize(l->getVelocity())*dLength*0.5f);
	glm::vec3 ahead3 = t->getPosition();

	if (glm::distance(ahead, tt->getPosition()) < tc->getBoundingRadius() || glm::distance(ahead2, tt->getPosition()) < tc->getBoundingRadius() || glm::distance(ahead3, tt->getPosition()) < tc->getBoundingRadius())
		return target;

	return nullptr;
}

void AISystem::process(Component *object)
{
	SteeringComponent *s = (SteeringComponent*)object->getSubComponent(ComponentType::STEERING);
	TransformComponent *t = (TransformComponent*)object->getSubComponent(ComponentType::TRANSFORM);
	LocomotionComponent *l = (LocomotionComponent*)object->getSubComponent(ComponentType::LOCOMOTION);

	glm::vec3 steering = glm::vec3(0.0f);

	if (s && t && l)
	{
		TransformComponent *tt;
		ColliderComponent *tc;
		glm::vec3 dv;
		int count=0;

		for (auto i : s->getBehaviours())
		{
			for (auto j : i->targets)
			{
				tt = (TransformComponent*)j->getSubComponent(ComponentType::TRANSFORM);
				tc = (ColliderComponent *)j->getSubComponent(ComponentType::COLLIDER);

				if (!tt || !tc)
					continue;

				float distance, dLength;
				switch (i->mode)
				{
				case Mode::SEEK:
					dv = glm::normalize(tt->getPosition() - t->getPosition()) * l->getMaxVel();
					steering += i->weight * (dv - l->getVelocity());
					count++;
					break;

				case Mode::FLEE:
					dv = glm::normalize(t->getPosition() - tt->getPosition()) * l->getMaxVel();
					steering += i->weight * (dv - l->getVelocity());
					count++;
					break;

				case Mode::ARRIVE:
					dv = tt->getPosition() - t->getPosition();
					distance = glm::length(dv);

					//Slowdown if near target
					if (distance < tc->getBoundingRadius() * 5)
						dv = glm::normalize(dv) * l->getMaxVel() * (distance / (tc->getBoundingRadius() * 5));
					else
						dv = glm::normalize(dv) * l->getMaxVel();

					steering += i->weight * (dv - l->getVelocity());
					count++;
					break;

				case Mode::AVOID:
					dLength = (glm::length(l->getVelocity()) / l->getMaxVel()) * 5.0f;
					glm::vec3 ahead = t->getPosition() + (glm::normalize(l->getVelocity())*dLength);
					glm::vec3 ahead2 = t->getPosition() + (glm::normalize(l->getVelocity())*dLength*0.5f);
					glm::vec3 ahead3 = t->getPosition();

					if (glm::distance(ahead, tt->getPosition()) < 3*tc->getBoundingRadius())
					{
						dv = ahead - tt->getPosition();
						dv = glm::normalize(dv) * 100.0f;

						steering += i->weight*dv;
						count++;
					}
					else if (glm::distance(ahead2, tt->getPosition()) < 3*tc->getBoundingRadius())
					{
						dv = ahead2 - tt->getPosition();
						dv = glm::normalize(dv) * 100.0f;

						steering += i->weight*dv;
						count++;
					}
					else if (glm::distance(ahead3, tt->getPosition()) < 3*tc->getBoundingRadius())
					{
						dv = ahead3 - tt->getPosition();
						dv = glm::normalize(dv) * 100.0f;

						steering += i->weight*dv;
						count++;
					}

					break;
				}
			}
		}

		if (count)
		{
			steering /= count;
			steering = truncat(steering, l->getMaxforce());
			steering /= l->getMass();
		}

		s->setSteering(steering);
	}
}