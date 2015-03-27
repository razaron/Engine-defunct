#include "Space.hpp"


Space::Space(System *s)
{
	mySystem = s;
}


Space::~Space()
{
}

void Space::update(double delta)
{
	if (mySystem != nullptr && !gameobjects.empty())
		mySystem->update(gameobjects, delta);

	for (auto i : subspaces)
		i->update(delta);
}

unsigned Space::addObject(Component *gameobject)
{
	if (std::find(gameobjects.begin(), gameobjects.end(), gameobject) != gameobjects.end())
		return gameobject->getHandle();

	gameobjects.push_back(gameobject);

	return gameobject->getHandle();
}

unsigned Space::addSubSpace(Space *space)
{
	if (std::find(subspaces.begin(), subspaces.end(), space) != subspaces.end())
		return 0;

	subspaces.push_back(space);

	return 1;
}