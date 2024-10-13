#include <iostream>

#include "Engine.h"
#include "System/Window.h"

int main(int argc, char** argv) {

	std::cout << "Sup?\n";

	auto app = App::Get();

	app->Run();

	App::Destroy();
	
	Window* window = new Window;

	window->SpawnWindow("YEs", 800, 600, Window::CUSTOM);

	bool running = true;
	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event) > 0) {
			//Check for quit events
			switch (event.type){
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							running = false;
							break;
					}
			}
		}
	}

	//*(int*)0 = 0;
	
	return 0;

}