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

	const std::string tmpSavePath = file::GetEditorPath("tmp.sv");

	bool gameLogic = app->IsGameLogicEnabled();
	if (gameLogic) {
		if (ui::Button("Quit Game")) {
			app->DisableGameLogic();

			File file(tmpSavePath, File::READ);
			app->Load(&file);
		}
	}
	else {
		if (ui::Button("Play Game")) {
			File file(tmpSavePath, File::WRITE);
			app->Save(&file, true);

			app->EnableGameLogic();
		}
	}

	/*ui::Prop("Run Logic", &gameLogic);
	if (gameLogic) {
		app->EnableGameLogic();
	}
	else {
		app->DisableGameLogic();
	}*/

	glm::vec2 size = { ui::GetRemainingWidth(), ui::GetRemainingHeight() };
	m_editorUI->viewport.forceAspect = size.x / size.y;

	ui::Image(m_editorUI->viewport.GetTexture(0), size);
}
