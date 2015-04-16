#include "MeshComponent.hpp"


MeshComponent::MeshComponent()
	//:Component(ComponentType::MESH)
{
	setType(ComponentType::MESH);
	glGenBuffers(1, &ebo);
}

MeshComponent::MeshComponent(float *data, int dataSize)
	:data(data), dataSize(dataSize)
{
	setType(ComponentType::MESH);
	glGenBuffers(1, &ebo);
}

MeshComponent::MeshComponent(float *data, int dataSize, unsigned *elements, int elementsSize)
	: data(data), dataSize(dataSize), elements(elements), elementsSize(elementsSize)
{
	setType(ComponentType::MESH);
	glGenBuffers(1, &ebo);
}

MeshComponent::~MeshComponent()
{
}
