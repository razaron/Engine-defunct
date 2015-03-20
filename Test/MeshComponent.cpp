#include "MeshComponent.hpp"


MeshComponent::MeshComponent()
	//:Component("meshcomponent")
{
	setType("meshcomponent");
}

MeshComponent::MeshComponent(float *data, int dataSize)
	:data(data), dataSize(dataSize)
{
	setType("meshcomponent");
}

MeshComponent::MeshComponent(float *data, int dataSize, unsigned *elements, int elementsSize)
	: data(data), dataSize(dataSize), elements(elements), elementsSize(elementsSize)
{
	setType("meshcomponent");
}

MeshComponent::~MeshComponent()
{
}
