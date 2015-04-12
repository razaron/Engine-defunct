#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

class Ray
{
public:
	Ray(glm::vec3 p1, glm::vec3 p2);
	~Ray();

	glm::vec3 getPos(){ return pos; };
	//void setPos(glm::vec3 pos){ this->pos = pos; };

	glm::vec3 getDir(){ return dir; };
	//void setDir(glm::vec3 dir){ this->dir = dir; };

	float getLength(){ return length; };
private:
	glm::vec3 pos, dir;
	float length;
};

