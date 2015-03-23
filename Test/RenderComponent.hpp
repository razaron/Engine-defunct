#pragma once

#include "Component.hpp"
#include "TransformComponent.hpp"
#include "MeshComponent.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

class RenderComponent : public Component
{
public:
	RenderComponent();
	RenderComponent(glm::vec3 position, glm::vec3 scale);
	RenderComponent(glm::vec3 position, glm::vec3 scale, MeshComponent *mesh);
	~RenderComponent();

	glm::vec3 getOvColour(){ return ovColour; };
	void setOvColour(glm::vec3 ovColor){ this->ovColour = ovColor; };
	float getAlpha(){ return alpha; };
	void setAlpha(float alpha){ this->alpha = alpha; };
	float getBoundingRadius(){ return boundingRadius; };
	void setBoundingRadius(float boundingRadius){ this->boundingRadius = boundingRadius; };

private:
	glm::vec3 ovColour;
	float alpha, boundingRadius;
};

