//pragma once just messes up if i have 2 files with the same name

#ifndef ENGINE_H
#define ENGINE_H

#include "System/Window.h"
#include "System/Input.h"

#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Graphics.h"
#include "Graphics/Textures/ImageTexture.h"
#include "Graphics/FrameBuffer.h"

class App {
private:
	App();
	virtual ~App();
public:

	void Run();

	// If finalFbo = nullptr, it will render to screen
	void Render(FrameBuffer* finalFbo = nullptr);

	//Singleton related:
	static App* Get();
	static void Destroy();
	static bool IsInitialized();

	Input input;

private:
	static App* singletonInstance;
	bool gameLoop;
	Window window;

	// By default it renders to the default FBO and then to screen
	// using the postShader
	// If I want to use the output in the editor i render it to
	// another FBO
	FrameBuffer* m_defaultFbo;
	Shader* m_postShader;

	Shader* defaultShader;

	Mesh*   m_defaultPlane;
	ImageTexture* m_testImage;
};

#endif //ENGINE_H