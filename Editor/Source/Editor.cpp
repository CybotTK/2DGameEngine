#include <iostream>

#include "Engine.h"

#include "EngineEditorUI.h"

int main(int argc, char** argv) {
	auto app = App::Get();

	app->AddEditorUI(new EngineEditorUI());

	app->Initialize();
	app->Run();

	App::Destroy();
	
	return 0;

}