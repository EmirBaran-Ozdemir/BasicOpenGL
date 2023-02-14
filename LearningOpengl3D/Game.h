#pragma once
#include "libs.h"

//. Enumarations
enum shader_enum { SHADER_CORE_PROGRAM = 0 };
enum texture_enum { TEX_FACE = 0, TEX_FACE_SPEC, TEX_CONTAINER, TEX_CONTAINER_SPEC };
enum material_enum { MAT_1 = 0 };
enum mesh_enum { MESH_TEST = 0, MESH_BG};

class Game
{
private:
	//. Variables
		//! Window
	GLFWwindow* window;
	Camera* camera;
	const int WINDOW_WIDTH, WINDOW_HEIGHT;
	int framebufferWidth, framebufferHeight;
	
	//! OpenGL Context
	const int GL_VERSION_MAJOR, GL_VERSION_MINOR;
	
	//! Delta time
	float dt;
	float curTime;
	float lastTime;

	//! Mouse input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;


	//! View Matrices
	glm::mat4 viewMatrix;
	glm::vec3 cameraPos;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	//! projection Matrices
	glm::mat4 projectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;
	//! Shaders
	std::vector<Shader*> shaders;

	//! Textures
	std::vector<Texture*> textures;

	//! Materials
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	std::vector<Material*> materials;


	//! Meshes
	std::vector<Mesh*> meshes;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 bgPosition;
	glm::vec3 bgScale;

	//! Lights
	std::vector<glm::vec3*> lights;

	//. Private Functions
	void initGLFW();
	void initWindow(const char* title, const bool resizable);
	void initGLEW();
	void initOpenGLOptions();
	void initMatrices();
	void initShaders();
	void initTextures();
	void initMaterials();
	void initMeshes();
	void initLights();
	void initUniforms();
	void updateUniforms();
	
	//. Static Variables

public:
	//. Constructor-Desturctor
	Game(
		const char* title,
		const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
		const int GL_VERSION_MAJOR, const int GLMinGL_VERSION_MINORorVer,
		bool resizable);
	virtual ~Game();

	//. Accesors
	int getWindowShouldClose();
	
	//. Modifiers
	void setWindowSouldClose();
	
	//. Functions
	void update(Mesh& mesh);
	void render();
	void updateKeyboardInput(Mesh& mesh);
	void updateMouseInput();
	void updateInput(Mesh& mesh);
	void updateDt();
	void frame_buffer_resize_callback(int fbW, int fbH);
	////. Static Funcitons
	//static void frame_buffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
	//static void updateInput(GLFWwindow* window, Mesh& mesh);

	//. Static Funcitons
	
};


