#pragma once

#include <string>
#include <vector>

static unsigned sNextId = 0;

class Component
{
public:
	Component();
	Component(std::string type);
	~Component();

	unsigned getHandle();
	std::string getType();
	std::vector<Component*> getComponentList();
	void setType(std::string type){ this->type = type; };

	int getComponentCount(Component *c);

	Component* getSubComponent(unsigned int handle); //returns Component from handle
	Component* getSubComponent(std::string type); //returns Component from type
	std::vector<Component*> getSubComponents(std::string type);
	unsigned addComponent(Component *c); // Adds component to GameObject and returns Component handle

private:
	unsigned handle;
	std::string type, name;
	
	std::vector<unsigned> parentHandles;
	std::vector <Component*> subComponents;
	
	unsigned getNextId() { return ++sNextId; };
};

