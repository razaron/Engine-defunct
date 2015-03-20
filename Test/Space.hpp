#pragma once

#include "System.hpp"

class Space
{
public:
	Space(System *s);
	~Space();
	void update();
	unsigned addObject(Component *gameobject);
	unsigned addSubSpace(Space *space);

private:
	System *mySystem;
	std::vector<Component*> gameobjects;

	std::vector<Space*> subspaces;
};

