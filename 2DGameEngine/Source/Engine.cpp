#include "Engine.h"
#include "System/Window.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

App* App::singletonInstance = nullptr;

App::App() {
	gameLoop = true;
}

App::~App() {
}

App* App::Get() {
	if (!IsInitialized()) {
		singletonInstance = new App();
	}
	return singletonInstance;
}

void App::Destroy() {
	if (IsInitialized()) {
		delete singletonInstance;
	}
	singletonInstance = nullptr;
}

bool App::IsInitialized() {
	return singletonInstance != nullptr;
}

void App::Run() {
	/*while (gameLoop) {
		window.SwapBuffers();
	}
	*/
	std::cout << "hello";
}
