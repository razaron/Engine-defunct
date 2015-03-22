#include "RenderSystem.hpp"


RenderSystem::RenderSystem(int width, int height)
	:width(width), height(height), root(new SceneNode())
{
	addType("rendercomponent");
	addType("meshcomponent");
	addType("transformcomponent");

	openWindow();
	shaderMain = new ShaderProgram();
	createShader(shaderMain, "Main.vert", NULL, "Main.frag");
	glUseProgram(shaderMain->program);

	camera = new Camera(glm::vec3(0.0f, 10.0f, 10.0f), glm::vec3(0.0f));

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / height, 1.0f, 100.0f);
	glUniformMatrix4fv(shaderMain->uniProjection, 1, GL_FALSE, glm::value_ptr(proj));
}

RenderSystem::~RenderSystem()
{
	closeWindow();
}

void setMainAttribs(ShaderProgram *shader)
{
	GLint posAttrib = glGetAttribLocation(shader->program, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

	GLint texAttrib = glGetAttribLocation(shader->program, "colour");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
}

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

void RenderSystem::setAttribs(ShaderProgram *shader)
{
	if (shader == shaderMain)
		setMainAttribs(shader);
}

VertexArray* RenderSystem::getVAO(MeshComponent *mesh, ShaderProgram *shader)
{
	for (auto i : vaos)
	{
		if (i->shader == shader)
		{
			for (auto j : i->meshes)
			{
				if (mesh == j)
					return i;
			}
		}
	}

	return nullptr;
}

void RenderSystem::addVAO(MeshComponent *mesh, ShaderProgram *shader)
{
	//If the mesh already has a VAO
	if (getVAO(mesh, shader) != nullptr)
		return;

	//If the mesh finds a suitable VAO, registers itself
	for (auto i : vaos)
	{
		if (i->meshes.at(0)->getData() == mesh->getData() && i->meshes.at(0)->getDataSize() == mesh->getDataSize())
		{
			i->meshes.push_back(mesh);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getEBO());
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getElementsSize()*sizeof(GLuint), mesh->getElements(), GL_STATIC_DRAW);

			return;
		}
	}
	
	//Makes a new VAO
	VertexArray *vao = new VertexArray;
	vao->meshes.push_back(mesh);
	vao->shader = shader;

	glGenVertexArrays(1, &vao->vao);
	glBindVertexArray(vao->vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->getDataSize() * sizeof(GLfloat), (void*)mesh->getData(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getEBO());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getElementsSize()*sizeof(GLuint), mesh->getElements(), GL_STATIC_DRAW);

	setAttribs(shader);

	glBindVertexArray(0);

	vaos.push_back(vao);
}

void RenderSystem::update(std::vector<Component*> gameobjects)
{
	delete root;
	root = new SceneNode();

	for (auto i : gameobjects)
	{
		process(i);
	}
}

void RenderSystem::processSubComponents(Component *c, SceneNode *n)
{
	for (auto j : c->getComponentList())
	{
		SceneNode *temp = n;
	
		if (j->getType() == "rendercomponent")
			{
				RenderComponent *r = (RenderComponent*)j;
				temp = new SceneNode();
				
				n->addChild(temp);
			}

		if (j->getType() == "transformcomponent")
			{
				TransformComponent *t = (TransformComponent*)j;
				temp->setTransform(t->getTransform());
				temp->setScale(t->getScale());
			}

		if (j->getType() == "meshcomponent")
			{
				temp->setMesh((MeshComponent*)j);
				addVAO((MeshComponent*)j, shaderMain);
			}

			
			
		processSubComponents(j, temp);
	}
}

void RenderSystem::process(Component *gameobject)
{
	SceneNode *temp = root;

	if (gameobject->getType() == "rendercomponent")
	{
		RenderComponent *r = (RenderComponent*)gameobject;
		temp = new SceneNode();

		root->addChild(temp);
	}
	

	processSubComponents(gameobject, temp);
}

void RenderSystem::updateScene(float delta)
{
	root->update(delta);
}

void RenderSystem::renderScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniformMatrix4fv(shaderMain->uniView, 1, GL_FALSE, glm::value_ptr(camera->getView()));

	glEnable(GL_DEPTH_TEST);

	drawNode(root);
}

void RenderSystem::draw(SceneNode *n)
{
	VertexArray *va = getVAO(n->getMesh(), shaderMain);

	if (va == nullptr)
		return;

	glBindVertexArray(va->vao);

	glm::mat4 model = glm::scale(n->getWorldTransform(), n->getScale());

	glUniformMatrix4fv(shaderMain->uniModel, 1, GL_FALSE, glm::value_ptr(model));
	//glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, n->getMesh()->getEBO());
	glDrawElements(GL_TRIANGLES, n->getMesh()->getElementsSize(), GL_UNSIGNED_INT, (void*)0);

	glBindVertexArray(0);

	checkError();
}

void RenderSystem::drawNode(SceneNode *n)
{
	draw(n);

	for (auto i : n->getChildren())
		drawNode(i);
}

GLFWwindow* RenderSystem::openWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr); // Windowed
	//GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	checkError();

	return window;
}

void RenderSystem::closeWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLuint RenderSystem::createShader(ShaderProgram *shader, char* vertexSource, char* geometrySource, char* fragmentSource)
{
	/* compile vertex shader */
	shader->vertex = glCreateShader(GL_VERTEX_SHADER);

	char* vert = readTextFile(vertexSource);
	glShaderSource(shader->vertex, 1, (const GLchar**)&vert, NULL);

	glCompileShader(shader->vertex);
	checkShaderCompile(shader->vertex);

	/* compile geometry shader */
	shader->geometry = glCreateShader(GL_GEOMETRY_SHADER);
	if (geometrySource != NULL)
	{
		char* geom = readTextFile(geometrySource);
		glShaderSource(shader->geometry, 1, (const GLchar**)&geom, NULL);

		glCompileShader(shader->geometry);
		checkShaderCompile(shader->geometry);

		free(geom);
	}


	/* compile fragment shader */
	shader->fragment = glCreateShader(GL_FRAGMENT_SHADER);

	char* frag = readTextFile(fragmentSource);
	glShaderSource(shader->fragment, 1, (const GLchar**)&frag, NULL);

	glCompileShader(shader->fragment);
	checkShaderCompile(shader->fragment);

	/* link shaders */
	shader->program = glCreateProgram();
	glAttachShader(shader->program, shader->vertex);

	if (geometrySource != NULL)
		glAttachShader(shader->program, shader->geometry);

	glAttachShader(shader->program, shader->fragment);
	glBindFragDataLocation(shader->program, 0, "outColor");

	glLinkProgram(shader->program);

	shader->uniModel = glGetUniformLocation(shader->program, "model");
	shader->uniView = glGetUniformLocation(shader->program, "view");
	shader->uniProjection = glGetUniformLocation(shader->program, "projection");
	shader->uniOvColour = glGetUniformLocation(shader->program, "ovColour");

	return shader->program;
}

char* RenderSystem::readTextFile(char* fileName)
{
	FILE *f;
	fopen_s(&f, fileName, "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *text = (char *)malloc(fsize + 1);
	fread(text, fsize, 1, f);
	fclose(f);

	text[fsize] = 0;

	return text;
}

void RenderSystem::checkShaderCompile(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		std::cout << buffer << "\n";
	}
}