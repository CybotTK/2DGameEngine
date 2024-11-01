#include "Engine.h"
#include "System/Window.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Graphics.h"

#include "Graphics/Shaders/BasicShaders.h"

App* App::singletonInstance = nullptr;

App::App() {
	gameLoop = true;
	
	testPlane = Mesh::CreatePlane();
	defaultShader = new Shader(shader::BasicVertex, shader::BasicFragment);
}

App::~App() {
	delete testPlane;
	delete defaultShader;
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
	while (gameLoop) {
		input.Update();
		if (input.GetQuitStatus()){
			gameLoop = false;
		}

		graphics::ClearBuffers(0.f, 0.3f, 1.f, 1.f);

		defaultShader->Use();

		testPlane->Use();
		testPlane->Draw();

		window.SwapBuffers();
	}
	
	std::cout << "hello";
}
