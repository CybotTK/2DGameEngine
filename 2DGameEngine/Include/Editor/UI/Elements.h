#ifndef EDITOR_UI_ELEMENTS_H
#define EDITOR_UI_ELEMENTS_H

#include <string>
#include <glm/glm.hpp>

#include "Graphics/Texture.h"

namespace ui {
	typedef std::string Icon;

	float GetCursorX();
	float GetCursorY();
	glm::vec2 GetCursor();

	void SetCursorX(float value);
	void SetCursorY(float value);
	void SetCursor(glm::vec2 value);

	float GetWidth(bool minusScrollSize = true);
	float GetHeight();

	float GetRemainingWidth();
	float GetRemainingHeight();

	void SameLine(float offsetX = 0.0f, float spacing = -1.0f);
	void Separator();

	void PushID(int id);
	void PushID(void* id);
	void PushID(const std::string& id);
	void PopID();

	bool Button(const std::string& text, glm::vec2 size = { 0.f, 0.f });

	void Text(const std::string& text);

	bool Header(const std::string& name, bool defaultOpen = true);

	void Image(Texture* image, glm::vec2 size = {0.f, 0.f}, bool flipY = true, glm::vec4 tint = {1.f, 1.f, 1.f, 1.f});
}

namespace uiInternal {
	void DrawPropPrefix(const std::string& name, const ui::Icon& icon);
}

#endif // !EDITOR_UI_ELEMENTS_H
