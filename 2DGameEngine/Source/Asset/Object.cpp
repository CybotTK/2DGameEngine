#include "Asset/Object.h"

#include "Engine.h"

#include "Editor/ImGui/imgui.h"
#include "Editor/UI/Props.h"

Object::Object() {

}

Object::~Object() {
	auto app = App::Get();
	auto editor = app->GetEditor();
	
	if (editor->selected == this) {
		editor->selected = nullptr;
	}
}

void Object::Save(File* file) {

}

void Object::Load(File* file) {

}

void Object::DrawUI() {
	ui::Text("Details tab hasn't been implemented for this!");
}

bool Object::DrawIcon(Texture* thumbnail) {
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));

	bool result = false;

	const float bSize = 45.f;
	const float bPad = 5.f;

	ui::PushID(this);
	{
		glm::vec2 posStart = ui::GetCursor();

		result = ImGui::Button("", ImVec2(ui::GetRemainingWidth(), bSize));
		glm::vec2 posNext = ui::GetCursor();

		ui::SetCursor(posStart);
		if (debug.thumbnail) {
			ui::Image(debug.thumbnail, { bSize, bSize }, false);
		}
		else if (thumbnail) {
			ui::Image(thumbnail, { bSize, bSize }, false);
		}

		ui::SetCursor(posStart + glm::vec2(bSize + bPad, bPad));
		ui::Text(debug.name);

		ui::SetCursorX(posStart.x + bSize + bPad);
		ui::Text(debug.description);

		ui::SetCursor(posNext);
	}
	ui::PopID();

	ImGui::PopStyleColor(2);

	return result;
}
