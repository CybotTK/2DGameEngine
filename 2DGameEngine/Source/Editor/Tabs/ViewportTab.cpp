#include "Editor/Tabs/ViewportTab.h"

#include "Editor/EditorUI.h"

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

	ImGui::Text("Viewport Test");

	bool gameLogic = app->IsGameLogicEnabled();
	ImGui::Checkbox("Run Logic", &gameLogic);

	if (gameLogic) {
		app->EnableGameLogic();
	}
	else {
		app->DisableGameLogic();
	}

	ImGui::Image(
		m_editorUI->viewport.GetTexture(0)->GetTextureID(),
		{ 1280.f, 720.f },			// Size
		{ 0.f, 1.f }, { 1.f, 0.f }, // UV0, UV1
		{ 1.f, 1.f, 1.f, 1.f }		// Tint
	);
}
