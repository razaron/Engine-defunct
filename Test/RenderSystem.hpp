#pragma once

#include "System.hpp"
#include "SceneNode.hpp"
#include "Camera.hpp"
#include "RenderComponent.hpp"

#include <GL/glew.h>  
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

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

	virtual void update(std::vector<Component*> gameobjects) override;
	virtual void process(Component *component) override;
	void processSubComponents(Component *c, SceneNode *n);

	GLFWwindow *getWindow(){ return window; };
	SceneNode *getRoot(){ return root; };
	Camera *getCamera(){ return camera; };
	VertexArray* getVAO(MeshComponent *mesh, ShaderProgram *shader);

	void setAttribs(ShaderProgram *shader);
	void addVAO(MeshComponent *mesh, ShaderProgram *shader);

	GLFWwindow* openWindow();
	void closeWindow();
	void updateScene(float delta);
	void renderScene();
	GLuint createShader(ShaderProgram *shader, char* vertexSource, char* geometrySource, char* fragmentSource);


private:
	void drawNode(SceneNode *n);
	char* readTextFile(char* fileName);
	void checkShaderCompile(GLuint shader);
	void draw(SceneNode *n);

	int width, height;
	GLFWwindow *window;
	ShaderProgram *shaderPre, *shaderMain, *shaderPost;
	std::vector<VertexArray*> vaos;

	SceneNode *root;
	Camera *camera;
};

