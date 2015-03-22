#include "Component.hpp"


Component::Component()
{
	handle = getNextId();
}

Component::Component(std::string type)
	:type(type)
{
	handle = getNextId();
}

Component::~Component()
{
}

unsigned Component::getHandle()
{
	return handle;
}

std::string Component::getType()
{
	return type;
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


Component* Component::getSubComponent(std::string type)
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