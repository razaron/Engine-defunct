#include "Space.hpp"


Space::Space(System *s)
{
	mySystem = s;
}


Space::~Space()
{
}

void Space::update()
{
	if (mySystem != nullptr && !gameobjects.empty())
		mySystem->update(gameobjects);

	for (auto i : subspaces)
		i->update();
}

unsigned Space::addObject(Component *gameobject)
{
	gameobjects.push_back(gameobject);

	return gameobject->getHandle();
}

unsigned Space::addSubSpace(Space *space)
{
	subspaces.push_back(space);

	return 0;
}