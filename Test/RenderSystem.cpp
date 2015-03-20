#include "RenderSystem.hpp"

float vertice[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 

	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 
	0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 

	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 
	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
};

float vertices[] = {
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f
};

unsigned elements[] = {
	0, 1, 2, 0, 2, 3,
	7, 0, 3, 3, 7, 6,
	3, 5, 6, 3, 2, 5,
	1, 4, 2, 2, 4, 5,
	7, 4, 0, 4, 1, 0,
	7, 5, 4, 7, 6, 5
};

GLuint vao;

RenderSystem::RenderSystem(int width, int height)
	:width(width), height(height), root(new SceneNode(glm::vec3(0.0f), glm::vec3(0.1f)))
{
	addType("rendercomponent");
	addType("meshcomponent");

	openWindow();
	shaderMain = new ShaderProgram();
	createShader(shaderMain, "Main.vert", NULL, "Main.frag");
	glUseProgram(shaderMain->program);

	camera = new Camera(glm::vec3(0.0f, 10.0f, 10.0f), glm::vec3(0.0f));

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / height, 1.0f, 100.0f);
	glUniformMatrix4fv(shaderMain->uniProjection, 1, GL_FALSE, glm::value_ptr(proj));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertice), vertice, GL_STATIC_DRAW);

	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(shaderMain->program, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

	GLint texAttrib = glGetAttribLocation(shaderMain->program, "colour");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
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
		if (i->meshes.at(0)->getData() == mesh->getData())
		{
			i->meshes.push_back(mesh);
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

	setAttribs(shader);

	glBindVertexArray(0);

	vaos.push_back(vao);
}

void RenderSystem::update(std::vector<Component*> gameobjects)
{
	delete root;
	root = new SceneNode(glm::vec3(0.0f), glm::vec3(0.1f));

	for (auto i : myTypes)
	{
		for (auto j : gameobjects)
		{
			if (j->getType() == i)
				process(j);
		}
	}
}

void RenderSystem::processSubComponents(Component *c, SceneNode *n)
{
	for (auto i : myTypes)
	{
		for (auto j : c->getComponentList())
		{
			SceneNode *temp = n;
			
			if (j->getType() == i)
			{
				if (i == "rendercomponent")
				{
					RenderComponent *r = (RenderComponent*)j;
					temp = new SceneNode(r->getPosition(), r->getScale());
					temp->setRotation(r->getRotation());
					
					n->addChild(temp);
				}

				if (i == "meshcomponent")
				{
					temp->setMesh((MeshComponent*)c);
					addVAO((MeshComponent*)c, shaderMain);
				}

			}
			
			processSubComponents(j, temp);
		}
	}
}

void RenderSystem::process(Component *component)
{
	SceneNode *temp = root;

	if (component->getType() == "rendercomponent")
	{
		RenderComponent *r = (RenderComponent*)component;

		temp = new SceneNode(r->getPosition(), r->getScale());
		temp->setRotation(r->getRotation());


		root->addChild(temp);
	}
	

	processSubComponents(component, temp);
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
	glm::mat4 model = glm::scale(n->getWorldTransform(), n->getScale());
	//model *= glm::rotate(n->getRotation(), glm::vec3(0.0f,0.0f,1.0f));

	glUniformMatrix4fv(shaderMain->uniModel, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
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