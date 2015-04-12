#include "Space.hpp"
#include "RenderSystem.hpp"
#include "PhysicsSystem.hpp"
#include "AISystem.hpp"

#include <iostream>
#include <stdlib.h>
#include <cmath>

float vertices[] = {
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.3f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.3f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.3f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.3f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.3f,
	-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.3f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.3f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.3f
};

float svertices[] = {
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.3f,
	0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.3f,
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.3f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.3f
};

unsigned elements[] = {
	0, 1, 2,	0, 2, 3,
	7, 0, 3,	3, 7, 6,
	3, 5, 6,	3, 2, 5,
	1, 4, 2,	2, 4, 5,
	7, 4, 0,	4, 1, 0,
	7, 5, 4,	7, 6, 5
};

float *vground;
unsigned *eground;


void makeGround(int x, int y)
{
	vground = (float*)malloc(7 * sizeof(float)*((x + 1)*(y + 1)));

	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			float *temp = &vground[7 * ((i*x) + j)];
			temp[0] = (float)i-(x/2);
			temp[1] = (float)j-(y/2);
			temp[2] = (float)((std::rand() % 100) / 100.0f);
			temp[3] = 1.0f;
			temp[4] = 1.0f;
			temp[5] = 1.0f;
			temp[6] = 0.0f;
		}
	}

	eground = (unsigned*)malloc(sizeof(float)*x*y * 6);

	int indicesIndex = 0;
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			int start = i * x + j;
			eground[indicesIndex++] = (short)start;
			eground[indicesIndex++] = (short)(start + 1);
			eground[indicesIndex++] = (short)(start + x);
			eground[indicesIndex++] = (short)(start + 1);
			eground[indicesIndex++] = (short)(start + 1 + x);
			eground[indicesIndex++] = (short)(start + x);
		}
	}
}


int main()
{
	RenderSystem r(800, 600);
	PhysicsSystem p;
	AISystem a;
	Space sp(&p);
	Space sr(&r);
	Space sa(&a);
	Space s(nullptr);
	
	s.addSubSpace(&sa);
	s.addSubSpace(&sp);
	s.addSubSpace(&sr);

	MeshComponent mSquare(svertices, 28, elements, 6);
	MeshComponent mCube(vertices, 56, elements, 36);

	//make floor panes
	RenderComponent floor(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(32.0f, 32.0f, 0.0f), &mSquare);
	floor.setAlpha(0.5f);
	RenderComponent floor2(glm::vec3(0.0f, 0.0f, -0.5f), glm::vec3(32.0f, 32.0f, 0.0f), &mSquare);
	floor2.setAlpha(0.5f);
	RenderComponent floor3(glm::vec3(0.0f, 0.0f, -0.5f), glm::vec3(32.0f, 32.0f, 0.0f), &mSquare);
	floor3.setAlpha(0.5f);

	floor.addComponent(&floor2);
	floor2.addComponent(&floor3);
	
	//make bullet
	RenderComponent bullet(glm::vec3(-10.0f, -11.0f, 3.0f), glm::vec3(0.5, 0.5f, 0.5f), &mCube);
	bullet.setOvColour(glm::vec3(0.0f, 1.0f, 0.0f));
	ColliderComponent cbullet(glm::vec3(0.0f, 5.0f, 2.7f), 0.25f);
	cbullet.setIsTrigger(true);
	bullet.addComponent((Component*)&cbullet);

	//make obstacles
	RenderComponent obstacle(glm::vec3(-5.0f, -5.0f, 3.0f), glm::vec3(2.0f, 2.0f, 2.0f), &mCube);
	ColliderComponent cobstacle(glm::vec3(0.0f, -5.0f, 3.0f), 1.0f);
	obstacle.addComponent(&cobstacle);

	RenderComponent obstacle2(glm::vec3(-5.0f, 5.0f, 3.0f), glm::vec3(2.0f, 2.0f, 2.0f), &mCube);
	ColliderComponent cobstacle2(glm::vec3(0.0f, -5.0f, 3.0f), 1.0f);
	obstacle2.addComponent(&cobstacle2);

	RenderComponent obstacle3(glm::vec3(5.0f, 5.0f, 3.0f), glm::vec3(2.0f, 2.0f, 2.0f), &mCube);
	ColliderComponent cobstacle3(glm::vec3(0.0f, -5.0f, 3.0f), 1.0f);
	obstacle3.addComponent(&cobstacle3);

	RenderComponent obstacle4(glm::vec3(5.0f, -5.0f, 3.0f), glm::vec3(2.0f, 2.0f, 2.0f), &mCube);
	ColliderComponent cobstacle4(glm::vec3(0.0f, -5.0f, 3.0f), 1.0f);
	obstacle4.addComponent(&cobstacle4);
	
	//make humanoid
	RenderComponent body(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(2.0, 2.0f, 2.0f), &mCube);
	ColliderComponent cbody(glm::vec3(0.0f, 0.0f, 3.0f), 1.0f);
	cbody.setIsTrigger(true);

	SteeringComponent sbody;
	Behaviour b1, b2;
	b1.mode = Mode::ARRIVE;
	b1.targets.push_back(&bullet);
	b2.mode = Mode::AVOID;
	b2.weight = 1.f;
	b2.targets.push_back(&obstacle);
	b2.targets.push_back(&obstacle2);
	b2.targets.push_back(&obstacle3);
	b2.targets.push_back(&obstacle4);
	sbody.addBehaviour(&b1);
	sbody.addBehaviour(&b2);

	LocomotionComponent lbody(10.0f, 1.0f, 10.0f);
	body.addComponent((Component*)&cbody);
	body.addComponent((Component*)&sbody);
	body.addComponent((Component*)&lbody);

	RenderComponent larm(glm::vec3(0.8f, 0.0f, -1.9f), glm::vec3(0.3f, 0.3f, -1.8f), &mCube);
	RenderComponent rarm(glm::vec3(-0.8f, 0.0f, -1.9f), glm::vec3(0.3f, 0.3f, -1.8f), &mCube);
	RenderComponent lleg(glm::vec3(1.2f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, -1.8f), &mCube);
	RenderComponent rleg(glm::vec3(-1.2f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, -1.8f), &mCube);
	RenderComponent head(glm::vec3(0.0f, 0.0f, 1.5f), glm::vec3(0.5f, 0.5f, 0.5f), &mCube);
	body.addComponent((Component*)&larm);
	body.addComponent((Component*)&rarm);
	body.addComponent((Component*)&lleg);
	body.addComponent((Component*)&rleg);
	body.addComponent((Component*)&head);

	//add body and bullet to the floor and put objects into their respective spaces
	floor.addComponent(&body);
	floor.addComponent(&bullet);
	floor.addComponent(&obstacle);
	floor.addComponent(&obstacle2);
	floor.addComponent(&obstacle3);
	floor.addComponent(&obstacle4);
	sr.addObject(&floor);
	sp.addObject(&obstacle);
	sp.addObject(&obstacle2);
	sp.addObject(&obstacle3);
	sp.addObject(&obstacle4);
	sp.addObject((Component*)&body);
	sp.addObject((Component*)&bullet);
	sa.addObject((Component*)&body);

	((TransformComponent*)body.getSubComponent("transformcomponent"))->setDeepScale(glm::vec3(1.0f));

	//CAMERA AND STUFF
	r.getCamera()->setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
	r.getCamera()->setPosition(glm::vec3(0.0f, 1.0f, 25.0f));
	r.setClearColour(glm::vec3(1.0f, 1.0f, 1.0f));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	body.setAlpha(0.5f);
	double time = glfwGetTime(), delta = 0;
	double lastTime = time;
	int nbFrames = 0;
	while (!glfwWindowShouldClose(r.getWindow()))
	{
		if (glfwGetKey(r.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(r.getWindow(), 1);

		if (glfwGetMouseButton(r.getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(r.getWindow(), &x, &y);
			
			//project mouse to ray in world coords
			Ray ray = r.mouseRay(x, y);

			//calculate ray x,y coords at z=3.f
			float ratio = (ray.getPos().z - 3.f) / (ray.getPos().z - (ray.getPos().z+(ray.getDir().z*ray.getLength())));
			glm::vec3 final = ray.getPos() + ray.getDir()*ray.getLength()*ratio;

			((TransformComponent*)bullet.getSubComponent("transformcomponent"))->setPosition(glm::vec3(final.x, final.y, final.z));
		}


		nbFrames++;
		if (time - lastTime >= 1.0){ // If last prinf() was more than 1 sec ago
			// printf and reset timer
			printf("%f ms/frame, %d FPS\n", 1000.0 / double(nbFrames), nbFrames);
			nbFrames = 0;
			lastTime += 1.0;
		}

		//r.getCamera()->setZoom(45.0f+std::abs(45.0f*std::sin(time)));
		//r.getCamera()->setPosition(glm::vec3(32 * std::sin(time), 32 * std::cos(time), 10.0f+(2.0 * std::sin(time))));
		//((TransformComponent*)bullet.getSubComponent("transformcomponent"))->setPosition(glm::vec3( 3.0f * std::sin(time/2), 0.0f, 3.0f));

		s.update(delta);
		r.updateScene(delta);
		r.renderScene();

		if (cbody.getCollidingWith() == &cbullet)
		{
			//((TransformComponent*)bullet.getSubComponent("transformcomponent"))->setPosition(glm::vec3((std::rand() % 32) - 16.0f, (std::rand() % 32) - 16.0f, 3.0f));
			((ColliderComponent*)bullet.getSubComponent("collidercomponent"))->getAABB()->updatePosition(((TransformComponent*)bullet.getSubComponent("transformcomponent"))->getPosition());
		}

		glfwSwapBuffers(r.getWindow());
		glfwPollEvents();

		delta = glfwGetTime()-time;
		time = glfwGetTime();
	}
	return 0;
}

/*
#define GLSL(src) "#version 150 core\n" #src

// Vertex shader
const GLchar* vertexShaderSrc = GLSL(
	in vec2 pos;

void main() {
	gl_Position = vec4(pos, 0.0, 1.0);
}
);

// Fragment shader
const GLchar* fragmentShaderSrc = GLSL(
	out vec4 outColor;
void main() {
	outColor = vec4(1.0, 0.0, 0.0, 1.0);
}
);

float vertices[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
};

GLuint elements[] = {
	0, 1, 2,
	2, 3, 0
};

void checkError()
{
	GLenum en = glGetError();
	switch (en)
	{
	//case GL_NO_ERROR: std::cout << "GL_NO_ERROR" << std::endl; break;
	case GL_INVALID_ENUM: std::cout << "GL_INVALID_ENUM" << std::endl; break;
	case GL_INVALID_VALUE: std::cout << "GL_INVALID_VALUE" << std::endl; break;
	case GL_INVALID_OPERATION: std::cout << "GL_INVALID_OPERATION" << std::endl; break;
	case GL_INVALID_FRAMEBUFFER_OPERATION: std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl; break;
	case GL_OUT_OF_MEMORY: std::cout << "GL_OUT_OF_MEMORY" << std::endl; break;
	case GL_STACK_UNDERFLOW: std::cout << "GL_STACK_UNDERFLOW" << std::endl; break;
	case GL_STACK_OVERFLOW: std::cout << "GL_STACK_OVERFLOW" << std::endl; break;
	}
}




int main(void)
{
	Renderer r(800, 600);
	r.openWindow();
	r.setup(vertices, elements);
	
	ShaderProgram shader;
	r.createShader(&shader, "Geom.vert", "Geom.geom", "Geom.frag");
	glUseProgram(shader.program);

	// Create VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// Create VBO with point coordinates
	GLuint vbo;
	glGenBuffers(1, &vbo);

	float points[] = {
		//  Coordinates  Color             Sides
		-0.45f, 0.45f, 1.0f, 0.0f, 0.0f, 4.0f,
		0.45f, 0.45f, 0.0f, 1.0f, 0.0f, 8.0f,
		0.45f, -0.45f, 0.0f, 0.0f, 1.0f, 16.0f,
		-0.45f, -0.45f, 1.0f, 1.0f, 0.0f, 32.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	

	// Specify layout of point data
	GLint posAttrib = glGetAttribLocation(shader.program, "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
		6 * sizeof(float), 0);

	GLint colAttrib = glGetAttribLocation(shader.program, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(float), (void*)(2 * sizeof(float)));

	GLint sidesAttrib = glGetAttribLocation(shader.program, "sides");
	glEnableVertexAttribArray(sidesAttrib);
	glVertexAttribPointer(sidesAttrib, 1, GL_FLOAT, GL_FALSE,
		6 * sizeof(float), (void*)(5 * sizeof(float)));


	while (glfwGetKey(r.window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glfwPollEvents();
		
		//r.update();
		
		// Render frame
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_POINTS, 0, 4);

		glfwSwapBuffers(r.window);
		checkError();
	}

	r.closeWindow();

	exit(EXIT_SUCCESS);
}
*/