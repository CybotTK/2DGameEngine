#include "Editor/Tabs/ViewportTab.h"

#include "Editor/EditorUI.h"
#include "Editor/UI/Props.h"
#include "Editor/ImGui/imgui.h"

#include "Engine.h"

ViewportTab::ViewportTab(EditorUI* editor) {
	name = "Viewport";
	m_editorUI = editor;
}

ViewportTab::~ViewportTab() {
}

void ViewportTab::DrawUI() {
	auto app = App::Get();

	ui::Text("Viewport Test");

	bool gameLogic = app->IsGameLogicEnabled();
	ui::Prop("Run Logic", &gameLogic);

	if (gameLogic) {
		app->EnableGameLogic();
	}
	else {
		app->DisableGameLogic();
	}

	glm::vec2 size = { ui::GetRemainingWidth(), ui::GetRemainingHeight() };
	m_editorUI->viewport.forceAspect = size.x / size.y;

	ui::Image(m_editorUI->viewport.GetTexture(0), size);
}
