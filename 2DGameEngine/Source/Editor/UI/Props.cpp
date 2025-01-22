#include "Editor/UI/Props.h"

#include "Editor/ImGui/imgui.h"

void ui::PropRange(const std::string& name, float* valueMin, float* valueMax, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);

	ImGui::DragFloatRange2(("##" + name).c_str(), valueMin, valueMax, 0.f, 0.f, 0.f, "Min: ", "Max: ", ImGuiSliderFlags_AlwaysClamp);
}

void ui::PropColor(const std::string& name, glm::vec3* value, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);

	ImVec4 color(value->x, value->y, value->z, 1.f);
	float w = ui::GetRemainingWidth();
	if (ImGui::ColorButton(("##" + name).c_str(), color, 0, { w, 0 })) {
		ImGui::OpenPopup(("Color Picker 3 ##" + name).c_str());
	}

	if (ImGui::BeginPopup(("Color Picker 3 ##" + name).c_str())) {
		ImGui::ColorPicker3(("##" + name).c_str(), (float*)&value[0]);
		ImGui::EndPopup();
	}
}

void ui::PropColor(const std::string& name, glm::vec4* value, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);

	ImVec4 color(value->x, value->y, value->z, 1.f);
	float w = ui::GetRemainingWidth();
	if (ImGui::ColorButton(("##" + name).c_str(), color, 0, { w, 0 })) {
		ImGui::OpenPopup(("Color Picker 4 ##" + name).c_str());
	}

	if (ImGui::BeginPopup(("Color Picker 4 ##" + name).c_str())) {
		ImGui::ColorPicker4(("##" + name).c_str(), (float*)&value[0]);
		ImGui::EndPopup();
	}
}

void ui::PropSlider(const std::string& name, float* value, glm::vec2 range, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);
	ImGui::SliderFloat(("##" + name).c_str(), value, range.x, range.y);
}

void ui::PropSlider(const std::string& name, int* value, glm::ivec2 range, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);
	ImGui::SliderInt(("##" + name).c_str(), value, range.x, range.y);
}

void ui::PropSlider(const std::string& name, glm::vec2* value, glm::vec2 range, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);
	ImGui::SliderFloat2(("##" + name).c_str(), (float*)&value->x, range.x, range.y);
}

void ui::PropSlider(const std::string& name, glm::ivec2* value, glm::ivec2 range, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);
	ImGui::SliderInt2(("##" + name).c_str(), (int*)&value->x, range.x, range.y);
}
