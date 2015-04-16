#pragma once

#include "Component.hpp"

#include <iostream>
#include <string>

class System
{
public:
	System();
	~System();
	virtual void update(std::vector<Component*> gameobjects, double delta);

	void addType(ComponentType type){ myTypes.push_back(type); };

protected:
	virtual void process(Component *component);
	std::vector<ComponentType> myTypes;

private:
};

