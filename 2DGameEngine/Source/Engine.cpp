#include "Engine.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Graphics/Shaders/BasicShaders.h"

#include "System/FileUtils.h"

App* App::singletonInstance = nullptr;

App::App() {
	gameLoop = true;
	
	m_defaultFbo = new FrameBuffer(1280, 720, 1);
	m_postShader = new Shader(shader::PostVertex, shader::PostFragment);
	defaultShader = new Shader(shader::BasicVertex, shader::BasicFragment);

	m_defaultPlane = Mesh::CreatePlane();
	m_testImage = new ImageTexture(file::GetEditorPath("..\\Assets\\test.png"));
}

App::~App() {
	delete m_testImage;
	delete m_defaultPlane;
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

		Render(nullptr);

		m_window.SwapBuffers();
	}
	
	std::cout << "hello";
}



void App::Render(FrameBuffer* finalFbo)
{
	//First we render the main thingy
	{
		m_defaultFbo->Use();
		auto res = m_defaultFbo->GetResolution();
		graphics::SetViewport(0, 0, res.x, res.y);

		graphics::ClearBuffers(0.f, 0.3f, 1.f, 1.f);

		defaultShader->Use();

		//Transform test
		{
			static Transform transf;
			transf.position = { .5f, .5f };
			transf.scale = { 0.3f, 0.3f };
			transf.rotation += 0.1f;

			auto mat = transf.GetMatrix();
			defaultShader->Set("transform", transf.GetMatrix());
		}

		//Binding a test image...
		defaultShader->Set("testImage", 0);
		m_testImage->Use(0);

		m_defaultPlane->Use();
		m_defaultPlane->Draw();
	}

	//Then we render final image
	{
		if (finalFbo) { 
			finalFbo->Use(); 
			auto res = finalFbo->GetResolution();
			graphics::SetViewport(0, 0, res.x, res.y);
		}
		else { 
			FrameBuffer::UseDefault(); //Screen
			m_window.UpdateViewport();
		}
		graphics::ClearBuffers(0.f, 0.3f, 1.f, 1.f);

		m_postShader->Use();
		m_postShader->Set("renderedTexture", 0);

		m_defaultFbo->UseAllTextures();

		m_defaultPlane->Use();
		m_defaultPlane->Draw();
	}
}