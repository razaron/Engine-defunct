#pragma once

#include <string>
#include <vector>
#include <algorithm>

static unsigned sNextId = 0;

enum class ComponentType{RENDER, MESH, TRANSFORM, LOCOMOTION, COLLIDER, CONTROLLER, STEERING};

class Component
{
public:
	Component();
	Component(bool isData);
	Component(ComponentType type);
	Component(ComponentType type, bool isData);
	~Component();

	unsigned getHandle(){
		if (isData)
			return 0;
		return handle;
	};
	ComponentType getType(){ return type; };
	void setType(ComponentType type){ this->type = type; };
	std::vector<Component*> getComponentList();

	int getComponentCount(Component *c);

	Component* getSubComponent(unsigned int handle); //returns Component from handle
	Component* getSubComponent(ComponentType type); //returns Component from type
	std::vector<Component*> getSubComponents(ComponentType type);
	unsigned addComponent(Component *c); // Adds component to GameObject and returns Component handle

	void removeSubComponents(Component *subComponent){ subComponents.erase(std::remove(subComponents.begin(), subComponents.end(), subComponent), subComponents.end()); };

private:
	unsigned handle;
	//std::string type, name;
	ComponentType type;
	bool isData;
	
	std::vector<unsigned> parentHandles;
	std::vector <Component*> subComponents;
	
	unsigned getNextId() { return ++sNextId; };
};

