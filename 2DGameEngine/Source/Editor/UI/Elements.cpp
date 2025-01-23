#include "Editor/UI/Elements.h"

#include "Editor/ImGui/imgui.h"

float ui::GetCursorX() {
	return ImGui::GetCursorPosX();
}

float ui::GetCursorY() {
	return ImGui::GetCursorPosY();
}

void ui::SetCursorX(float value) {
	ImGui::SetCursorPosX(value);
}

void ui::SetCursorY(float value) {
	ImGui::SetCursorPosY(value);
}

float ui::GetWidth(bool minusScrollSize) {
	float out = ImGui::GetWindowWidth();
	if (minusScrollSize) {
		ImGuiStyle* style = &ImGui::GetStyle();
		out -= style->ScrollbarSize;
	}

	return out;
}

float ui::GetHeight() {
	return ImGui::GetWindowHeight();
}

float ui::GetRemainingWidth() {
	return ui::GetWidth() - ui::GetCursorX();
}

float ui::GetRemainingHeight() {
	return ui::GetHeight() - ui::GetCursorY();
}

void ui::SameLine(float offsetX, float spacing) {
	ImGui::SameLine(offsetX, spacing);
}

void ui::Separator() {
	ImGui::Separator();
}

void ui::PushID(int id) {
	ImGui::PushID(id);
}

void ui::PushID(void* id) {
	ImGui::PushID(id);
}

void ui::PushID(const std::string& id) {
	ImGui::PushID(id.c_str());
}

void ui::PopID() {
	ImGui::PopID();
}


void ui::Text(const std::string& text) {
	ImGui::Text(text.c_str());
}

bool ui::Header(const std::string& name) {
	return ImGui::CollapsingHeader(name.c_str());
}

void ui::Image(Texture* image, glm::vec2 size, bool flipY, glm::vec4 tint) {
	assert(image);

	ImVec2 uv0(0.f, 0.f);
	ImVec2 uv1(1.f, 1.f);

	if (flipY) {
		uv0 = { 0.f, 1.f };
		uv1 = { 1.f, 0.f };
	}

	if (size == glm::vec2(0.f)) {
		size.x = ui::GetRemainingWidth();
		size.y = size.x / image->GetAspectRatio();
	}
	if (size.x == 0) { size.x = ui::GetRemainingWidth(); }
	if (size.y == 0) { size.y = ui::GetRemainingHeight(); }

	ImGui::Image(
		image->GetTextureID(),
		{ size.x, size.y },
		uv0, uv1,
		{ tint.x, tint.y, tint.z, tint.w }
	);
}

//=======================================//

void uiInternal::DrawPropPrefix(const std::string& name, const ui::Icon& icon) {
	float start = ui::GetCursorX();

	ui::SetCursorX(start+20);
	if (icon != "") {
		ImGui::Text(icon.c_str());
		ui::SameLine();
		ui::SetCursorX(start + 46);
	}
	ImGui::Text(name.c_str());
	ui::SameLine();

	//Setting the cursor
	float width = ui::GetWidth();
	const float halfWidth = width * 0.5f;

	ui::SetCursorX(halfWidth);
	ImGui::SetNextItemWidth(width - halfWidth);
}
