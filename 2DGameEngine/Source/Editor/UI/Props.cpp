#include "Editor/UI/Props.h"

#include "Editor/ImGui/imgui.h"

#define SHOW_BITS_L 8

void ui::PropMask(const std::string& name, uint16_t* mask, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);

	float start = ui::GetCursorX();
	float w = ui::GetRemainingWidth() / SHOW_BITS_L;
	glm::vec2 size(w - 1.f, 0.f);

	ImGuiStyle* style = &ImGui::GetStyle();

	auto backupSpacing = style->ItemSpacing;
	style->ItemSpacing.y = 0;

	auto backupPadding = style->FramePadding;
	style->FramePadding.y = 3;

	for (int column = 0; column < 2; column++) {
		size_t c = column * SHOW_BITS_L;

		for (size_t i = 0; i < SHOW_BITS_L; i++) {
			ui::SetCursorX(start + w * i);

			bool bit = (*mask >> (i + c)) & 1;
			ImGui::PushStyleColor(ImGuiCol_Button,
				bit ? ImVec4(0.02352f, 0.5f, 0.56f, 1.f) : ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
			auto result = ImGui::Button(
				("##BM" + name + std::to_string(i + c + 10)).c_str(),
				ImVec2(size.x, size.y)
			);
			if (result) {
				bit = !bit;
			}
			ImGui::PopStyleColor(1);
			/*ui::ButtonCheckbox(
				"##BM" + name + std::to_string(i + c + 10),
				bit, "", size
			);*/
			//value->Set(i + c, bit);
			if (bit) {
				*mask |= 1 << (i + c);
			}
			else {
				*mask &= ~(1 << (i + c));
			}

			if (ImGui::IsItemHovered()) {
				ImGui::BeginTooltip();
				ui::Text("Bit " + std::to_string(i + c) + (bit ? " (Enabled)" : " (Disabled)"));
				ImGui::EndTooltip();
			}

			if (i < (SHOW_BITS_L - 1)) {
				ui::SameLine();
			}
		}
	}

	style->ItemSpacing = backupSpacing;
	style->FramePadding = backupPadding;

	ImGui::Dummy({ 1,3 });
}

void ui::ObjectHeader(std::string* name, const std::string& className, const ui::Icon& icon) {
	ui::Prop("Name", name);
	ui::PropText("Class", className, icon);
	ui::Separator();
}

void ui::PropText(const std::string& name, const std::string& text, const ui::Icon& icon) {
	uiInternal::DrawPropPrefix(name, icon);
	ImGui::Text(text.c_str());
}

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
