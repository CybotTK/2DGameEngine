#include "Engine.h"

#include "System/FileUtils.h"

int main(int argc, char** argv) {
	auto app = App::Get();

	File file(file::GetEditorPath("data.block"), File::READ);
	app->Load(&file, false);

	app->Initialize();
	app->Run();

	App::Destroy();

	return 0;
}