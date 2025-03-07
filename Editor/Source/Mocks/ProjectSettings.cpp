#include "Mocks/ProjectSettings.h"

#include "Engine.h"

#include "Editor/UI/Props.h"

ProjectSettings::ProjectSettings() {
}

ProjectSettings::~ProjectSettings() {
}

void ProjectSettings::DrawUI() {
	auto app = App::Get();
	auto fbo = app->GetFrameBuffer();

	ui::ObjectHeader(&app->projectName, "Project");

	app->project.mainScene.DrawUI("Main Scene");

	// Resolution
	{
		auto res = fbo->GetResolution();
		ui::Prop("Resolution", &res);

		if (res.x <= 32) { res.x = 32; }
		if (res.y <= 32) { res.y = 32; }

		fbo->Resize(res.x, res.y);
	}

}
