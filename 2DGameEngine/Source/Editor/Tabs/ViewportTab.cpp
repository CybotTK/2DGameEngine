#include "Editor/Tabs/ViewportTab.h"

#include "Editor/EditorUI.h"
#include "Editor/UI/Props.h"
#include "Editor/ImGui/imgui.h"

#include "System/FileUtils.h"
#include "System/File.h"

#include "Engine.h"

ViewportTab::ViewportTab(EditorUI* editor) {
	name = "Viewport";
	m_editorUI = editor;
}

ViewportTab::~ViewportTab() {
}

void ViewportTab::DrawUI() {
	auto app = App::Get();

	const std::string tempSavePath = file::GetEditorPath("temp.sv");

	bool gameLogic = app->IsGameLogicEnabled();
	if (gameLogic) {
		if (ui::Button("Quit Game")) {
			app->DisableGameLogic();

			// Backing up the current scene
			size_t sceneID = app->GetCurrentSceneID();

			File file(tempSavePath, File::READ);
			app->Load(&file);

			// Restoring the current scene
			app->SetCurrentScene(sceneID);
		}
	}
	else {
		if (ui::Button("Play Game")) {
			File file(tempSavePath, File::WRITE);
			app->Save(&file, true);

			app->EnableGameLogic();
		}
	}

	glm::vec2 size = { ui::GetRemainingWidth(), ui::GetRemainingHeight() };
	m_editorUI->viewport.forceAspect = size.x / size.y;

	ui::Image(m_editorUI->viewport.GetTexture(0), size);
}
