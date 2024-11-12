#include "System/Window.h"
#include <iostream>
#include <assert.h>
#include <GL/glew.h>

Window::Window(const std::string& title, Window::Type type) {
	SpawnWindow(title, 800, 600, type);
}

Window::Window(const std::string& title, int width, int height, Window::Type type) {
	SpawnWindow(title, width, height, type);
}

Window::~Window() {
	if (mainContext) {
		SDL_GL_DeleteContext(mainContext); // Delete OpenGL context
	}
	if (mainWindow) {
		SDL_DestroyWindow(mainWindow); //Destroy SDL window
	}
	
	SDL_Quit(); //Quit SDL
}

void Window::SetTitle(const std::string& title){
	SDL_SetWindowTitle(mainWindow, title.c_str());
}

glm::ivec2 Window::GetWindowSize(){
	int x, y;
	SDL_GL_GetDrawableSize(mainWindow, &x, &y);
	return glm::ivec2(x,y);
}

void Window::UpdateViewport() {
	auto res = glm::ivec2(GetWindowSize());
	graphics::SetViewport(0, 0, res.x, res.y);
}

void Window::SwapBuffers() {
	SDL_GL_SwapWindow(mainWindow); //Swap the buffers, showing the rendered content
}

SDL_Window* Window::GetSDLWindow() {
	return mainWindow;
}

SDL_GLContext Window::GetContext() {
	return mainContext;
}

void Window::SpawnWindow(const std::string& title, int width, int height, Window::Type type) {
	SDL_Init(SDL_INIT_EVERYTHING);

	//Setting maaany attributes cause:
	{
		const int rgbaSize = 8;

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, rgbaSize);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, rgbaSize);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, rgbaSize);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, rgbaSize);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

		//Setting context to OpenGL 4.6
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4.6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

		//Setting OpenGL Compatibility mode
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	}

	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	if (type == MAXIMIZED) {
		flags = flags | SDL_WINDOW_MAXIMIZED;
	}
	else if (type == FULLSCREEN) {
		flags = flags | SDL_WINDOW_FULLSCREEN;
	}

	mainWindow = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED, //X axis
		SDL_WINDOWPOS_CENTERED, //Y axis
		width, height, flags
	);

	//Checks if window is proprely created
	assert(mainWindow);

	if (!mainWindow) {
		std::cout << "Failed to create window\n";
	}

	//Create OpenGL context
	mainContext = SDL_GL_CreateContext(mainWindow);

	//Enable Vsync
	int vSyncResult = SDL_GL_SetSwapInterval(1);
	assert(vSyncResult == 0);
	
	//Set the window surface
	SDL_Surface* window_surface = SDL_GetWindowSurface(mainWindow);
	SDL_UpdateWindowSurface(mainWindow);

	//Initialize GLEW
	GLenum glewInitResult = glewInit();
	assert(glewInitResult == GLEW_OK);

	//GL stuff
	{
		glDisable(GL_DEPTH_TEST); // no need for depth in 2D
		glDisable(GL_CULL_FACE); // no need for culling in 2D, no geometry is accidentally culled
		glEnable(GL_MULTISAMPLE); // improves visual quality
	}

}

