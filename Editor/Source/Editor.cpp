#include <iostream>

#include "Engine.h"
#include "System/Window.h"

int main(int argc, char** argv) {
	auto app = App::Get();

	app->AddEditorUI(new EditorUI);

	app->Initialize();
	app->Run();

	App::Destroy();
	
	return 0;

}