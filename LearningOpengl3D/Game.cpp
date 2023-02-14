#include "Game.h"

//. Private Functions
void Game::initGLFW()
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::GLFW::FAILED_INITIALIZATION" << std::endl;
		glfwTerminate();
	}
}
void Game::initWindow(const char* title, const bool resizable)
{
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GLFW_TRUE); MAC-OS

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);
	if (this->window == nullptr)
	{
		std::cout << "ERRROR::GLFW::WINDOW_INITIALIZATION_FAILED" << std::endl;
		glfwTerminate();
	}

	auto frameBuffCall = [](GLFWwindow* window, int fbW, int fbH)
	{
		((Game*)glfwGetWindowUserPointer(window))->frame_buffer_resize_callback(fbW, fbH);
	};

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	glfwSetFramebufferSizeCallback(this->window, frameBuffCall);

	glfwMakeContextCurrent(this->window);
}
void Game::initGLEW()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::GLEW::INITIALIZATION_FAILED" << std::endl;
		glfwTerminate();
	}
}
void Game::initOpenGLOptions()
{
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Game::initMatrices()
{
	//this->viewMatrix = glm::mat4(1.f);
	//this->viewMatrix = glm::lookAt(this->cameraPos, this->cameraPos + this->camFront, this->worldUp);

	//this->projectionMatrix = glm::mat4(1.f);
	//projectionMatrix = glm::perspective(
	//	glm::radians(this->fov),
	//	static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
	//	this->nearPlane,
	//	this->farPlane
	//);
	//!: Create Camera
	camera = new Camera(static_cast<float>(this->framebufferWidth) / this->framebufferHeight, this->fov, this->nearPlane, this->farPlane, this->cameraPos, this->camFront);

}
void Game::initShaders()
{
	this->shaders.push_back(
		new Shader(
			this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
			(char*)"vertex_core.glsl", (char*)"fragment_core.glsl"
		));
}
void Game::initTextures()
{
	this->textures.push_back(new Texture("assets\\awesomeface.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("assets\\awesomeface_specular.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("assets\\container.jpg", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("assets\\container_specular.jpg", GL_TEXTURE_2D));
}
void Game::initMaterials()
{
	this->materials.push_back(new Material(
		this->ambient, this->diffuse, this->specular, 0, 1
	));
}
void Game::initMeshes()
{
	//Quad tempQuad = Quad();
	//this->meshes.push_back(new Mesh(&tempQuad, this->position, this->rotation, this->scale));
	float loop = 10;
	for (float i = 0; i < loop; i++)
	{
		for (size_t j = 0; j < loop; j++)
		{
			glm::vec3 objLocation(i - ((loop - 1) / 2), 0.f, j - ((loop - 1) / 2));
			Cube tempCube = Cube(objLocation);
			this->meshes.push_back(new Mesh(&tempCube, this->position, this->rotation, this->scale));
		}
	}
	Quad objBackground = Quad();
	this->meshes.push_back(new Mesh(&objBackground, this->bgPosition, this->rotation, this->bgScale));
}
void Game::initLights()
{
	this->lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}
void Game::initUniforms()
{
	this->shaders[SHADER_CORE_PROGRAM]->use();
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->camera->getViewMatrix(), "viewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->camera->getProjection(), "projectionMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->cameraPos, "cameraPos");
}
void Game::updateUniforms()
{
	//! Camera angle
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	//this->camera->getProjection() = glm::perspective(
	//		glm::radians(this->fov),
	//		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
	//		this->nearPlane,
	//		this->farPlane
	//	);

	camera->updateProjection(static_cast<float>(this->framebufferWidth) / this->framebufferHeight);


	//this->viewMatrix = glm::lookAt(this->cameraPos, this->cameraPos + this->camFront, this->worldUp);

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->camera->getProjection(), "projectionMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->camera->getViewMatrix(), "viewMatrix");
}

//. Constructor-Desturctor
Game::Game(
	const char* title,
	const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
	const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
	bool resizable)
	: WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT),
	GL_VERSION_MAJOR(GL_VERSION_MAJOR), GL_VERSION_MINOR(GL_VERSION_MINOR)
{
	//! Init variables
		//! Window
	this->window = nullptr;
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;
	//! View Matrices
	this->cameraPos = glm::vec3(0.f, 0.f, 1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);
	//! Projection Matrices
	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;
	//! Delta time
	this->dt = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;

	this->lastMouseX = 0.0;
	this->lastMouseY = 0.0;
	this->mouseX = 0.0;
	this->mouseY = 0.0;
	this->mouseOffsetX = 0.0;
	this->mouseOffsetY = 0.0;
	this->firstMouse = true;
	//! Materials
	this->ambient = glm::vec3(0.2f);
	this->diffuse = glm::vec3(1.f);
	this->specular = glm::vec3(1.f);
	//! Meshes
	this->position = glm::vec3(0.f);
	this->rotation = glm::vec3(0.f);
	this->scale = glm::vec3(1.f);
	this->bgPosition = glm::vec3(0.f, 0.f, -100.f);
	this->bgScale = glm::vec3(200.f);


	this->initGLFW();
	this->initWindow(title, resizable);
	this->initGLEW();
	this->initOpenGLOptions();
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initMeshes();
	this->initLights();
	this->initUniforms();
}

Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
	for (size_t i = 0; i < this->shaders.size(); i++)
		delete this->shaders[i];
	for (size_t i = 0; i < this->textures.size(); i++)
		delete this->textures[i];
	for (size_t i = 0; i < this->materials.size(); i++)
		delete this->materials[i];
	for (size_t i = 0; i < this->meshes.size(); i++)
		delete this->meshes[i];
	for (size_t i = 0; i < this->lights.size(); i++)
		delete this->lights[i];


}

//. Accesors
int Game::getWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

//. Modifiers
void Game::setWindowSouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

//. Functions
void Game::update(Mesh& mesh)
{
	//! Update input
	this->updateDt();
	this->updateInput(mesh);
}
void Game::render()
{
	//! Update
	//this->updateInput(*meshes[MESH_TEST]);
	//this->updateInput(*meshes[1]);
	for (std::vector<Mesh>::size_type i = 0; i != meshes.size() - 1; i++) {
		this->update(*meshes[i]);
	}
	//! Clear
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//! Update uniforms
	this->updateUniforms();
	this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

	//! Use program before drawing
	this->shaders[SHADER_CORE_PROGRAM]->use();

	//! Activate texture
	this->textures[TEX_CONTAINER]->bindTex(0);
	this->textures[TEX_CONTAINER_SPEC]->bindTex(1);

	for (std::vector<Mesh>::size_type i = 0; i != meshes.size(); i++) {
		this->meshes[i]->render(this->shaders[SHADER_CORE_PROGRAM]);
	}
	//this->meshes[MESH_TEST]->render(this->shaders[SHADER_CORE_PROGRAM]);
	//this->meshes[MESH_BG]->render(this->shaders[SHADER_CORE_PROGRAM]);

	//! End Draw
	glfwSwapBuffers(window);
	glFlush();

	//! Clear
	glBindVertexArray(0);
	this->textures[TEX_CONTAINER]->unbindTex();
	this->textures[TEX_CONTAINER_SPEC]->unbindTex();
	this->shaders[SHADER_CORE_PROGRAM]->unuse();
}
void Game::updateKeyboardInput(Mesh& mesh)
{

	{
		//! Exit Program
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		//CAMERA_DIR dir = CAMERA_DIR_NONE;
		//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		//{
		//	dir |= CAMERA_DIR_FRONT;
		//}
		//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		//{
		//	dir |= CAMERA_DIR_BACK;
		//}
		//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		//{
		//	dir |= CAMERA_DIR_LEFT;
		//}
		//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		//{
		//	dir |= CAMERA_DIR_RIGHT;
		//}
		//if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		//{
		//	dir |= CAMERA_DIR_DOWN;
		//}
		//if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		//{
		//	dir |= CAMERA_DIR_UP;
		//}
		//camera->move(dir);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			mesh.move(glm::vec3(0.f, 0.f, 0.001f));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			mesh.move(glm::vec3(0.f, 0.f, -0.001f));
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			mesh.move(glm::vec3(0.001f, 0.f, 0.f));
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			mesh.move(glm::vec3(-0.001f, 0.f, 0.f));
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			mesh.move(glm::vec3(0.f, 0.001f, 0.f));
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			mesh.move(glm::vec3(0.f, -0.001f, 0.f));
		}
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			//camFront += glm::vec3(0.001f, 0.f, 0.f);
			mesh.rotate(glm::vec3(-0.1f, 0.f, 0.f));
		}
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			//camFront += glm::vec3(-0.001f, 0.0f, 0.f);
			mesh.rotate(glm::vec3(0.1f, 0.f, 0.f));
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			//camFront += glm::vec3(0.001f, 0.f, 0.f);
			mesh.rotate(glm::vec3(0.f, -0.1f, 0.f));
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			//camFront += glm::vec3(-0.001f, 0.0f, 0.f);
			mesh.rotate(glm::vec3(0.f, 0.1f, 0.f));
		}
	}
}
void Game::updateMouseInput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse)
	{
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}
	//! Calc offset
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY;
	//! Set x,y
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;

}
void Game::updateInput(Mesh& mesh)
{
	glfwPollEvents();
	this->updateKeyboardInput(mesh);
	this->updateMouseInput();

}
void Game::updateDt()
{
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;
}

void Game::frame_buffer_resize_callback(int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}


//. Static Functions
