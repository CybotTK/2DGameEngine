//pragma once just messes up if i have 2 files with the same name

#ifndef ENGINE_H
#define ENGINE_H

#include "System/Window.h"
#include "System/Input.h"
#include "System/Timer.h"

#include "Audio/AudioTrack.h"

#include "Core/Transform.h"
#include "Core/Camera.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Asset/Asset.h"

#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Graphics.h"
#include "Graphics/Textures/ImageTexture.h"
#include "Graphics/FrameBuffer.h"

#include "Editor/EditorUI.h"

#include "System/File.h"

class App {
private:
	App();
	virtual ~App();
public:
	// We don't want to initialize everything since some of the stuff 
	// we will have will have a dependency on the App instance
	// That will mess things up! That's why we use this
	void Initialize();

	const float engineVersion = 1.0f;

	void Save(File* file, bool withEditor = true);
	void Load(File* file);

	//Main loop goes here
	void Run();

	// If finalFbo = nullptr, it will render to screen
	void Render(FrameBuffer* finalFbo = nullptr);

	Scene* GetCurrentScene();
	void SetCurrentScene(const std::string& name);
	void SetCurrentScene(size_t id);
	void SetCurrentScene(Scene* scene);

	float GetDeltaTime() const;

	void AddEditorUI(EditorUI* ui);
	bool HasEditorUI() const;
	bool IsGameLogicEnabled() const;

	EditorUI* GetEditor() const;

	void EnableGameLogic();
	void DisableGameLogic();

	//Singleton related:
	static App* Get();
	static void Destroy();
	static bool IsInitialized();

	Input input;
	Window m_window;

	struct Data {
		AssetMap<ImageTexture> images;
		AssetMap<Mesh>		   meshes;

		AssetMap<AudioTrack>   audios;

		AssetMap<Scene>		   scenes;
	} data;
private:
	void UpdateDeltaTime();

	static App* singletonInstance;

	Timer m_deltaTimer;
	float m_deltaTime = 0.f;

	Scene* m_currentScene;
	std::vector<Scene*> scenes;

	EditorUI* m_editorUI = nullptr;
	bool m_runGameLogic = true;

	bool m_gameLoop;

	// By default it renders to the default FBO and then to screen
	// using the postShader
	// If I want to use the output in the editor i render it to
	// another FBO
	FrameBuffer* m_defaultFbo;
	Shader* m_postShader;

	Shader* m_defaultShader;
	Mesh*   m_defaultPlane;
};

#endif //ENGINE_H