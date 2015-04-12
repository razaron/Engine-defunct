#pragma once

#include <string>
#include <vector>
#include <algorithm>

static unsigned sNextId = 0;

class Component
{
public:
	Component();
	Component(bool isData);
	Component(std::string type);
	Component(std::string type, bool isData);
	~Component();

	unsigned getHandle();
	std::string getType();
	void setType(std::string type){ this->type = type; };
	std::vector<Component*> getComponentList();

	int getComponentCount(Component *c);

	Component* getSubComponent(unsigned int handle); //returns Component from handle
	Component* getSubComponent(std::string type); //returns Component from type
	std::vector<Component*> getSubComponents(std::string type);
	unsigned addComponent(Component *c); // Adds component to GameObject and returns Component handle

	void removeSubComponents(Component *subComponent){ subComponents.erase(std::remove(subComponents.begin(), subComponents.end(), subComponent), subComponents.end()); };

private:
	unsigned handle;
	std::string type, name;
	bool isData;
	
	std::vector<unsigned> parentHandles;
	std::vector <Component*> subComponents;
	
	unsigned getNextId() { return ++sNextId; };
};

