//pragma once just messes up if i have 2 files with the same name

#ifndef ENGINE_H
#define ENGINE_H

#include "System/Window.h"
#include "System/Input.h"

#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Graphics.h"
#include "Graphics/Textures/ImageTexture.h"

class App {
private:
	App();
	virtual ~App();
public:

	void Run();

	//Singleton related:
	static App* Get();
	static void Destroy();
	static bool IsInitialized();

	Input input;

private:
	static App* singletonInstance;
	bool gameLoop;
	Window window;

	Shader* defaultShader;
	Mesh*   testPlane;
};

#endif //ENGINE_H