#include "Space.hpp"
#include "RenderSystem.hpp"

#include <iostream>
#include <stdlib.h>
#include <cmath>

float ertices[] = {
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f
};

unsigned lements[] = {
	0, 1, 2,	0, 2, 3,
	7, 0, 3,	3, 7, 6,
	3, 5, 6,	3, 2, 5,
	1, 4, 2,	2, 4, 5,
	7, 4, 0,	4, 1, 0,
	7, 5, 4,	7, 6, 5
};

int main()
{
	RenderSystem r(800, 600);
	Space t(&r);
	Space s(nullptr);
	
	s.addSubSpace(&t);

	RenderComponent body(glm::vec3(0.0f, 0.0f, -3.5f), glm::vec3(1.0, 0.5f, -1.5f));
	
	body.addComponent(new RenderComponent(glm::vec3(0.8f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, -1.8f)));
	body.addComponent(new RenderComponent(glm::vec3(-0.8f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, -1.8f)));
	body.addComponent(new RenderComponent(glm::vec3(1.2f, 0.0f, 3.0f), glm::vec3(0.3f, 0.3f, -1.8f)));
	body.addComponent(new RenderComponent(glm::vec3(-1.2f, 0.0f, 3.0f), glm::vec3(0.3f, 0.3f, -1.8f)));
	body.addComponent(new RenderComponent(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.5f, 0.5f, 0.5f)));

	t.addObject((Component*)&body);
	//body.setRotation(-5.0f);

	float time = glfwGetTime(), delta = 0;
	while (!glfwWindowShouldClose(r.getWindow()))
	{
		if (glfwGetKey(r.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(r.getWindow(), 1);


		//body.setPosition(glm::vec3(5*std::sin(time), 5*std::cos(time), 0.0f));
		
		s.update();
		r.updateScene(time);
		r.renderScene();

		glfwSwapBuffers(r.getWindow());
		glfwPollEvents();

		delta = time - glfwGetTime();
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