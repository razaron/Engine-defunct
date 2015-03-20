#include "SceneNode.hpp"

SceneNode::SceneNode()
	:parent(NULL), scale(glm::vec3(1.0f)), rotation(0.0f)
{
	
}

SceneNode::SceneNode(glm::vec3 position, glm::vec3 scale)
	: parent(NULL), scale(scale), rotation(0.0f)
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

unsigned SceneNode::update(float delta)
{
	if (rotation != 0.0f)
	{
		transform *= glm::rotate(rotation*delta, glm::vec3(1.0f, 1.0f, 0.0f));
	}

	if (parent)
		worldTransform = parent->worldTransform * transform;
	else
		worldTransform = transform;

	for (auto i : children)
		i->update(delta);

	return 0;
}