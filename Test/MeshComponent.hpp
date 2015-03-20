#pragma once

#include "Component.hpp"

#include <GL/glew.h>  
#include <GLFW/glfw3.h>

class MeshComponent : public Component
{
public:
	MeshComponent();
	MeshComponent(float *data, int dataSize);
	MeshComponent(float *data, int dataSize, unsigned *elements, int elementsSize);
	~MeshComponent();

	float* getData(){ return data; };
	int getDataSize(){ return dataSize; };
	unsigned* getElements(){ return elements; };
	int getElementsSize(){ return elementsSize; };

	GLuint getEBO(){ return ebo; };
	void setEBO(GLuint ebo){ this->ebo = ebo; };

	void setData(float *data){ this->data = data; };
	void setElements(unsigned *elements){ this->elements = elements; };
	void setDataSize(int data){ this->dataSize = data; };
	void setElementsSize(int elements){ this->elementsSize = elements; };

private:
	float *data;
	int dataSize;

	unsigned *elements;
	int elementsSize;
	GLuint ebo;
};

