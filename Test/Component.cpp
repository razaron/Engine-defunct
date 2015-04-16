#include "Component.hpp"


Component::Component()
	:isData(false)
{
	handle = getNextId();
}

Component::Component(bool isData)
	:isData(isData)
{
	if (!isData)
		handle = getNextId();
}

Component::Component(ComponentType type)
	:type(type), isData(false)
{
	handle = getNextId();
}

Component::Component(ComponentType type, bool isData)
	: type(type), isData(isData)
{
	if (!isData)
		handle = getNextId();
}

Component::~Component()
{
}

Component* Component::getSubComponent(unsigned int handle)
{
	for (auto i : subComponents)
	{
		if (i->getHandle() == handle)
			return i;
	}

	return nullptr;
}

//std::vector<Component*> Component::getSubComponents(std::string type)


Component* Component::getSubComponent(ComponentType type)
{
	for (auto i : subComponents)
	{
		if (i->getType() == type)
			return i;
	}

	return nullptr;
}

std::vector<Component*> Component::getComponentList()
{
	return subComponents;
}

unsigned Component::addComponent(Component *c)
{
	if (std::find(subComponents.begin(), subComponents.end(), c) != subComponents.end())
		return c->getHandle();

	subComponents.push_back(c);
	c->parentHandles.push_back(handle);

	return c->getHandle();
}

int Component::getComponentCount(Component *c)
{
	static int i = 1;
	
	Component *temp = c;
	while (temp->getComponentList().size())
	{
		i += temp->getComponentList().size();
		for (auto j : temp->getComponentList())
			getComponentCount(temp);
	}

	int count = i;
	i = 0;

	return count;
}