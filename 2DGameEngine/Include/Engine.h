//pragma once just messes up if i have 2 files with the same name

#ifndef ENGINE_H
#define ENGINE_H

#include "System/Window.h"

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
private:
	static App* singletonInstance;
	bool gameLoop;
	Window window;
};

#endif //ENGINE_H