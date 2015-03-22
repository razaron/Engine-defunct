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

private:
};

