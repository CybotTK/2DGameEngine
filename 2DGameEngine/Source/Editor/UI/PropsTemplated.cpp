#include "Editor/UI/Props.h"

#include "Editor/ImGui/imgui.h"

template<>
void ui::Prop(const std::string& name, int* value, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);
	ImGui::DragInt(("##" + name).c_str(), value, 0.1f, 0.f, 0.f);

}

template<>
void ui::Prop(const std::string& name, float* value, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);
	ImGui::DragFloat(("##" + name).c_str(), value, 0.1f, 0.f, 0.f);
}

template<>
void ui::Prop(const std::string& name, bool* value, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);
	//ui::SetCursorX(ui::GetWidth() - 26.f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 16.f);
	ImGui::Checkbox(("##" + name).c_str(), value);
	ImGui::PopStyleVar();
}

template<>
void ui::Prop(const std::string& name, std::string* value, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);

	char buf[128];
	strcpy_s(buf, value->c_str());
	ImGui::InputText(("##" + name).c_str(), buf, 128);
	*value = buf;
}

//============================//

template<>
void ui::Prop(const std::string& name, glm::vec2* value, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);
	ImGui::DragFloat2(("##" + name).c_str(), (float*)&value[0], 0.1f, 0, 0);
}

template<>
void ui::Prop(const std::string& name, glm::ivec2* value, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);
	ImGui::DragInt2(("##" + name).c_str(), (int*)&value[0], 0.1f, 0, 0);
}
