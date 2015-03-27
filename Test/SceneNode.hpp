#pragma once

#include "MeshComponent.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>
#include <malloc.h>

class SceneNode
{
public:
	SceneNode();
	SceneNode(glm::vec3 position, glm::vec3 scale);
	~SceneNode();
	void* operator new(std::size_t sz){
		return _aligned_malloc(sz, 16);
	};

	void operator delete(void* p)
	{
		_aligned_free(p);
	}


	MeshComponent* getMesh(){ return mesh; };
	glm::mat4 getWorldTransform(){ return worldTransform; };
	glm::mat4 getTransform(){ return transform; };
	glm::vec3 getScale(){ return scale; };
	std::vector<SceneNode*> getChildren(){ return children; };

	void setMesh(MeshComponent* mesh){ this->mesh = mesh; };
	void setWorldTransform(glm::mat4 t){ worldTransform = t; };
	void setTransform(glm::mat4 t){ transform = t; };
	void setScale(glm::vec3 s){ scale = s; };


	void addChild(SceneNode *s);
	virtual unsigned draw();
	virtual unsigned update(double delta);

	glm::vec3 getOvColour(){ return ovColour; };
	void setOvColour(glm::vec3 ovColor){ this->ovColour = ovColor; };
	float getAlpha(){ return alpha; };
	void setAlpha(float alpha){ this->alpha = alpha; };
	float getCameraDistance(){ return cameraDistance; };
	void setCameraDistance(float cameraDistance){ this->cameraDistance = cameraDistance; };
	float getBoundingRadius(){ return boundingRadius; };
	void setBoundingRadius(float boundingRadius){ this->boundingRadius = boundingRadius; };

private:
	
	SceneNode *parent;

	MeshComponent *mesh;
	glm::mat4 worldTransform;
	glm::mat4 transform;
	glm::vec3 scale;
	
	glm::vec3 ovColour;
	float alpha;
	float cameraDistance, boundingRadius;

	std::vector <SceneNode*> children;
};

