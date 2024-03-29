#pragma once

#include "System.hpp"
#include "SceneNode.hpp"
#include "Camera.hpp"
#include "RenderComponent.hpp"
#include "TransformComponent.hpp"
#include "ColliderComponent.hpp"
#include "Frustum.hpp"
#include "Ray.hpp"

#include <GL/glew.h>  
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <algorithm>

typedef struct shaderprogram ShaderProgram;
typedef struct vertexarray VertexArray;

struct shaderprogram
{
	GLuint vertex, geometry, fragment;
	GLint uniModel, uniView, uniProjection, uniOvColour;
	GLuint program;
};

struct vertexarray
{
	GLuint vao;
	ShaderProgram *shader;
	std::vector<MeshComponent*> meshes;
};


class RenderSystem : public System
{
public:
	RenderSystem(int width, int height);
	~RenderSystem();

	virtual void update(std::vector<Component*> gameobjects, double delta) override;
	virtual void process(Component *component) override;
	void processSubComponents(Component *c, SceneNode *n);

	void setClearColour(glm::vec3 colour){ clearColour = colour; };
	GLFWwindow *getWindow(){ return window; };
	SceneNode *getRoot(){ return root; };
	Camera *getCamera(){ return camera; };
	VertexArray* getVAO(MeshComponent *mesh, ShaderProgram *shader);

	void setAttribs(ShaderProgram *shader);
	void addVAO(MeshComponent *mesh, ShaderProgram *shader);

	GLFWwindow* openWindow();
	void closeWindow();
	void updateScene(double delta);
	void renderScene();
	GLuint createShader(ShaderProgram *shader, char* vertexSource, char* geometrySource, char* fragmentSource);

	void buildNodeLists(SceneNode* from);
	void sortNodeLists();

	Ray mouseRay(double x, double y);

private:
	void drawNode(SceneNode *n);
	char* readTextFile(char* fileName);
	void checkShaderCompile(GLuint shader);
	void draw(SceneNode *n);

	int width, height;
	GLFWwindow *window;
	glm::vec3 clearColour;
	ShaderProgram *shaderPre, *shaderMain, *shaderPost;
	std::vector<VertexArray*> vaos;

	SceneNode *root;
	std::vector<SceneNode*> opaqueNodes, transparentNodes;
	Camera *camera;
	Frustum frustum;
};

