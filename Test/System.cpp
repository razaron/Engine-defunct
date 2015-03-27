#include "System.hpp"

#include<string>
#include <algorithm>

System::System()
{
}


System::~System()
{
}

void System::update(std::vector<Component*> gameobjects, double delta)
{
	for (auto i : myTypes)
	{
		for (auto j : gameobjects)
		{
			Component *k = j->getSubComponent(i);
			if (k != nullptr)
				process(k);
		}
	}
}

void System::process(Component* component)
{

}
