#ifndef EDITOR_UI_PROPS_H
#define EDITOR_UI_PROPS_H

#include <string>
#include <glm/glm.hpp>

#include "Editor/UI/Elements.h"

namespace ui {
	template <typename T>
	void Prop(const std::string& name, T* value, const ui::Icon& icon = "");

	void ObjectHeader(std::string* name, const std::string& className, const ui::Icon& icon = "");

	void PropText(const std::string& name, const std::string& text, const ui::Icon& icon = "");

	void PropRange(const std::string& name, float* valueMin, float* valueMax, const ui::Icon& icon = "");

	void PropColor(const std::string& name, glm::vec3* value, const ui::Icon& icon = "");
	void PropColor(const std::string& name, glm::vec4* value, const ui::Icon& icon = "");

	void PropSlider(const std::string& name, float* value, glm::vec2 range = glm::vec2(0.f, 1.f), const ui::Icon& icon = "");
	void PropSlider(const std::string& name, int* value, glm::ivec2 range = glm::ivec2(0, 100), const ui::Icon& icon = "");

	void PropSlider(const std::string& name, glm::vec2* value, glm::vec2 range = glm::vec2(0.f, 1.f), const ui::Icon& icon = "");
	void PropSlider(const std::string& name, glm::ivec2* value, glm::ivec2 range = glm::ivec2(0, 100), const ui::Icon& icon = "");
}

#endif // !EDITOR_UI_PROPS_H
