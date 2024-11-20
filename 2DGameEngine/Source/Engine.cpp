#include "Engine.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Graphics/Shaders/BasicShaders.h"

#include "System/FileUtils.h"

App* App::singletonInstance = nullptr;

App::App() {
	m_gameLoop = true;
	
	m_defaultFbo = new FrameBuffer(1280, 720, 1);
	m_postShader = new Shader(shader::PostVertex, shader::PostFragment);
	
	m_defaultShader = new Shader(shader::BasicVertex, shader::BasicFragment);
	m_defaultPlane = Mesh::CreatePlane();
	
	data.meshes.Add("Plane", Mesh::CreatePlane());

	m_currentScene = nullptr;
}

App::~App() {
	data.images.Reset();
	data.meshes.Reset();
	data.scenes.Reset();

	delete m_defaultPlane;
	delete m_defaultShader;
}

void App::Run() {
	data.images.Add("test.png", new ImageTexture(file::GetEditorPath("..\\Assets\\test.png")));

	m_currentScene = new Scene();
	data.scenes.Add("Main Scene", m_currentScene);

	while (m_gameLoop) {
		input.Update();
		if (input.GetQuitStatus()) {
			m_gameLoop = false;
		}

		if (m_currentScene) {
			m_currentScene->Update();

			Render(nullptr);
		}

		m_window.SwapBuffers();
	}
}

void App::Render(FrameBuffer* finalFbo) {
	//First we render the main thingy
	{
		m_defaultFbo->Use();
		auto res = m_defaultFbo->GetResolution();
		graphics::SetViewport(0, 0, res.x, res.y);

		graphics::ClearBuffers(0.f, 0.3f, 1.f, 1.f);

		float aspect = finalFbo ? finalFbo->GetAspect() : m_window.GetAspect();
		m_currentScene->Draw(m_defaultShader, aspect);
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

Scene* App::GetCurrentScene(){
	return m_currentScene;
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