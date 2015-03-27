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

	void addType(std::string type){ myTypes.push_back(type); };

protected:
	virtual void process(Component *component);
	std::vector<std::string> myTypes;

private:
};

