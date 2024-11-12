#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "Graphics/Graphics.h"

class Window {
public:
	enum Type {
		CUSTOM,
		FULLSCREEN,
		MAXIMIZED
	};

	Window(const std::string& title = "Engine", Window::Type type = MAXIMIZED);
	Window(const std::string& title, int width, int height, Window::Type type = MAXIMIZED);
	virtual ~Window();

	void SetTitle(const std::string& title);

	glm::ivec2 GetWindowSize();
	void UpdateViewport();

	void SwapBuffers();

	void SpawnWindow(const std::string& title, int width, int height, Window::Type type = MAXIMIZED);

	//Getters for imGUI maybe
	SDL_Window* GetSDLWindow();
	SDL_GLContext GetContext();

private:

	SDL_Window* mainWindow;
	SDL_GLContext mainContext;

};

#endif // WINDOW_H
