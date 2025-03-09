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

	m_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
}

ViewportTab::~ViewportTab() {
}

float __Floor(float value) {
	float out = float(int(value));
	return out;
}

void ViewportTab::DrawUI() {
	auto app = App::Get();
	auto editor = app->GetEditor();
	auto& input = app->input;

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
	static float snapScale = 0.5f;
	ui::SameLine();
	ImGui::Text("Snap");
	ui::SameLine();
	ImGui::SliderFloat("##Snapping", &snapScale, 0.1f, 5.f);

	glm::vec2 size = { ui::GetRemainingWidth(), ui::GetRemainingHeight() };
	m_editorUI->viewport.forceAspect = size.x / size.y;

	ui::Image(m_editorUI->viewport.GetTexture(0), size);

	auto scene = app->GetCurrentScene();

	// Running the controls
	if (scene) {
		auto& cam = scene->camera;

		if (ImGui::IsWindowFocused() && ImGui::IsItemHovered()) {
			// Zooming the Camera with the mouse wheel
			float scroll = input.GetMouseScrollY();
			float scrollSpeed = glm::clamp(cam.area, 0.1f, 50.f) / 50.f;
			scrollSpeed = 0.4f + scrollSpeed * 2.f;
			cam.area -= scroll * scrollSpeed;
			if (cam.area <= 0.f) { cam.area = 0.1f; };

			// Calculate the Mouse offset (world)
			auto camVP = cam.GetViewProjection();
			auto invVP = glm::inverse(camVP);

			auto offset = input.GetMouseMotion();

			// We need to map it range [-1, 1]
			offset = (offset * 2.f) / size;

			auto localOffset = invVP * glm::vec4(offset.x, offset.y, 0.f, 0.f);
			offset = glm::vec2(localOffset.x, -localOffset.y);

			// Applying the offset when appropriate
			if (input.Active(InputKey::MOUSE_RIGHT)) {
				cam.position -= offset;
			}

			// Object controls
			GameObject* obj = dynamic_cast<GameObject*>(editor->selected);
			if (obj) {
				// First abordation of snapping
				/*if (input.Active(InputKey::MOUSE_LEFT)) {
					bool useSnap = input.Active(InputKey::KEY_LEFT_CTRL);

					if (useSnap) {
						if (offset.x > 0.f) {
							offset.x = glm::max(offset.x, snapScale);
						}
						else if (offset.x < 0.f) {
							offset.x = glm::min(offset.x, -snapScale);
						}
						if (offset.y > 0.f) {
							offset.y = glm::max(offset.y, snapScale);
						}
						else if (offset.y < 0.f) {
							offset.y = glm::min(offset.y, -snapScale);
						}
					}

					obj->position += offset;

					if (useSnap) {
						obj->position /= snapScale;
						obj->position.x = __Floor(obj->position.x);
						obj->position.y = __Floor(obj->position.y);
						obj->position *= snapScale;
					}
				}*/

				// Second abordation of snapping
				// When you press KEY_LEFT_CTRL and have MOUSE_LEFT released it snaps
				if (input.Active(InputKey::MOUSE_LEFT)) {
					obj->position += offset;
				}
				if (input.Active(InputKey::KEY_LEFT_CTRL) && input.Released(InputKey::MOUSE_LEFT)) {
					obj->position /= snapScale;
					obj->position.x = __Floor(obj->position.x);
					obj->position.y = __Floor(obj->position.y);
					obj->position *= snapScale;
				}
			}
		}
	}
}
