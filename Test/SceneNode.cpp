#include "SceneNode.hpp"

SceneNode::SceneNode()
	:parent(NULL), scale(glm::vec3(1.0f)), ovColour(glm::vec3(1.0f)), alpha(1.0f), boundingRadius(0.0f)
{
	
}

SceneNode::SceneNode(glm::vec3 position, glm::vec3 scale)
	: parent(NULL), scale(scale), ovColour(glm::vec3(1.0f)), alpha(1.0f), boundingRadius(0.0f)
{

	transform *= glm::translate(position);
}

SceneNode::~SceneNode()
{
	for (auto i : children)
		delete i;
}

void SceneNode::addChild(SceneNode *s)
{
	children.push_back(s);
	s->parent = this;
}

unsigned SceneNode::draw()
{

	return 0;
}

unsigned SceneNode::update(double delta)
{
	if (parent)
		worldTransform = parent->worldTransform * transform;
	else
		worldTransform = transform;

	for (auto i : children)
		i->update(delta);

	return 0;
}