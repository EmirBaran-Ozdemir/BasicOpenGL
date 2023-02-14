#include "Game.h"


int main()
{
	//. Init GLFW and Create window
	const char* WINDOW_TITLE = "MyWindow";
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 400;
	int framebufferWidth = 0;
	int framebufferHeight = 0;
	int GLMajorVer = 4;
	int GLMinorVer = 5;
	bool resizable = true;

	Game mainGame(
		WINDOW_TITLE, WINDOW_WIDTH,
		WINDOW_HEIGHT, GLMajorVer,
		GLMinorVer, resizable
	);
	//. Init GLEW
	//. OpenGL options
	//. Shader init
	//. Mesh
	//. Texture init
	//. Material
	//. Light-Model-View-Matrix
	//. Main Loop
	while (!mainGame.getWindowShouldClose())
	{
		//! Update input
		mainGame.render();

	}
	//. End
	return 0;
}
