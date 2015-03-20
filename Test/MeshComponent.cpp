#include "MeshComponent.hpp"


MeshComponent::MeshComponent()
	//:Component("meshcomponent")
{
	setType("meshcomponent");
	glGenBuffers(1, &ebo);
}

MeshComponent::MeshComponent(float *data, int dataSize)
	:data(data), dataSize(dataSize)
{
	setType("meshcomponent");
	glGenBuffers(1, &ebo);
}

MeshComponent::MeshComponent(float *data, int dataSize, unsigned *elements, int elementsSize)
	: data(data), dataSize(dataSize), elements(elements), elementsSize(elementsSize)
{
	setType("meshcomponent");
	glGenBuffers(1, &ebo);
}

MeshComponent::~MeshComponent()
{
}
