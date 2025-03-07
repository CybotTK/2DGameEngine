#include "Engine.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
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

	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

App::~App() {
	data.images.Reset();
	data.meshes.Reset();
	data.audios.Reset();
	data.scenes.Reset();

	delete m_defaultPlane;
	delete m_defaultShader;

	Mix_CloseAudio();
	SDL_Quit();
}

void App::Initialize() {
	// Testing
	{
		data.images.Add("test.png", new ImageTexture(file::GetEditorPath("..\\Assets\\test.png")));

		auto audioId = data.audios.Add("Ambience", new AudioTrack(file::GetEditorPath("..\\Assets\\Ambience.wav")));

		//Testing audio -- It works
		//data.audios[audioId].asset->Play();

		m_currentScene = new Scene();
		data.scenes.Add("Main Scene", m_currentScene);
	}

	if (!HasEditorUI()) {
		m_window.SetTitle(projectName);
	}
}

void App::ClearAll() {
	data.images.Reset();
	data.meshes.Reset();
	data.audios.Reset();
	data.scenes.Reset();
}

void App::Save(File* file, bool withEditor) {
	file->Write(engineVersion);
	file->Write(withEditor);

	file->WriteStr(projectName);
	file->Write(project);

	data.images.Save(file);
	data.meshes.Save(file);
	data.audios.Save(file);
	data.scenes.Save(file);
}

void App::Load(File* file) {
	float version;
	bool withEditor;
	file->Read(version);
	file->Read(withEditor);

	assert(version == engineVersion);
	if(HasEditorUI()) {
		// Prevents the user (that has access to this editor) 
		// from opening an exported game in the editor.
		// TOP SECURITY MEASURE
		// Idea got from: https://www.google.com/url?sa=i&url=https%3A%2F%2Fknowyourmeme.com%2Fmemes%2Fcheeto-lock&psig=AOvVaw2oEKj9kgjvT35hm0OHXJv9&ust=1740953528333000&source=images&cd=vfe&opi=89978449&ved=0CBQQjRxqFwoTCIi827bz6YsDFQAAAAAdAAAAABAs
		assert(withEditor == true);
		if (!withEditor) {
			return;
		}
	}

	// Project Settings
	file->ReadStr(projectName);
	file->Read(project);

	// Game Data
	data.images.Load(file);
	data.meshes.Load(file);
	data.audios.Load(file);
	data.scenes.Load(file);

	// Initialization
	{
		m_currentScene = project.mainScene.Get();
		if (m_currentScene == nullptr && data.scenes.size()) {
			// If no default scene is set, it selects any available scene
			m_currentScene = data.scenes.begin()->second.asset;
		}
	}
}

void App::Run() {
	m_deltaTimer.Reset();

	while (m_gameLoop) {
		UpdateDeltaTime();

		input.Update();
		if (input.GetQuitStatus()) {
			m_gameLoop = false;
		}

		if (m_currentScene) {
			if (m_runGameLogic) {
				m_currentScene->Update();
				m_currentScene->UpdatePhysics(m_deltaTime);
			}
			m_currentScene->EndUpdate();
		}

		if (m_editorUI) {
			Render(&m_editorUI->viewport);

			m_editorUI->UpdateAll();
			m_editorUI->Draw();
		}
		else {
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
		
		if (m_currentScene == nullptr) {
			AssetHandler<Scene> handle;
			handle.Set(data.scenes.begin()->first); // Set using the first scene's ID
			m_currentScene = handle.Get();          // Get the actual Scene*
		}
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

Scene* App::GetCurrentScene() {
	return m_currentScene;
}

size_t App::GetCurrentSceneID() const {
	for (auto it : data.scenes) {
		if (it.second.asset == m_currentScene) {
			return it.first;
		}
	}
	return 0;
}

void App::SetCurrentScene(const std::string& name) {
	AssetHandler<Scene> handle;
	handle.Set(name);

	m_currentScene = handle.Get();
}

void App::SetCurrentScene(size_t id) {
	m_currentScene = data.scenes[id].asset;
}

void App::SetCurrentScene(Scene* scene) {
	m_currentScene = scene;
}

float App::GetDeltaTime() const {
	return m_deltaTime;
}

void App::AddEditorUI(EditorUI* ui) {
	if (m_editorUI) {
		delete m_editorUI;
	}

	m_editorUI = ui;
	DisableGameLogic();
}

bool App::HasEditorUI() const {
	return m_editorUI != nullptr;
}

bool App::IsGameLogicEnabled() const {
	return m_runGameLogic;
}

EditorUI* App::GetEditor() const {
	return m_editorUI;
}

void App::EnableGameLogic() {
	m_runGameLogic = true;
}

void App::DisableGameLogic() {
	m_runGameLogic = false;
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

FrameBuffer* App::GetFrameBuffer() const {
	return m_defaultFbo;
}

void App::UpdateDeltaTime() {
	m_deltaTime = m_deltaTimer.Get();
	m_deltaTimer.Reset();

	if (m_deltaTime > 100.f) {
		//Avoiding some corner cases
		m_deltaTime = 1.f;
	}
}
