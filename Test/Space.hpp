#pragma once

#include "System.hpp"

#include <algorithm>

class Space
{
public:
	Space(System *s);
	~Space();
	void update(double delta);
	unsigned addObject(Component *gameobject);
	unsigned addSubSpace(Space *space);

	void removeObject(Component *gameobject){ gameobjects.erase(std::remove(gameobjects.begin(), gameobjects.end(), gameobject), gameobjects.end()); };

private:
	System *mySystem;
	std::vector<Component*> gameobjects;

	std::vector<Space*> subspaces;
};

