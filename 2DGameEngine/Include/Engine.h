//pragma once just messes up if i have 2 files with the same name

#ifndef ENGINE_H
#define ENGINE_H

#include "System/Window.h"
#include "System/Input.h"
#include "System/Timer.h"

#include "Core/Transform.h"
#include "Core/Camera.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Core/Asset.h"

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
	// We don't want to initialize everything since some of the stuff 
	// we will have will have a dependency on the App instance
	// That will mess things up! That's why we use this
	void Initialize();

	//Main loop goes here
	void Run();

	// If finalFbo = nullptr, it will render to screen
	void Render(FrameBuffer* finalFbo = nullptr);

	Scene* GetCurrentScene();

	float GetDeltaTime() const;

	//Singleton related:
	static App* Get();
	static void Destroy();
	static bool IsInitialized();

	Input input;

	struct Data {
		AssetMap<ImageTexture> images;
		AssetMap<Mesh>		   meshes;

		AssetMap<Scene>		   scenes;
	} data;
private:
	void UpdateDeltaTime();

	static App* singletonInstance;

	Timer m_deltaTimer;
	float m_deltaTime;

	Scene* m_currentScene;
	std::vector<Scene*> scenes;

	bool m_gameLoop;
	Window m_window;

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