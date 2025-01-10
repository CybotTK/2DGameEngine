#ifndef EDITOR_UI_H
#define EDITOR_UI_H

#include "Editor/EditorTab.h"
#include "Graphics/FrameBuffer.h"

class EditorUI {
public:
	EditorUI();
	virtual ~EditorUI();

	void Update();
	void Draw();

	FrameBuffer viewport;
	std::vector<EditorTab*> tabs;
protected:
	void RenderBegin();
	void Render();
	void RenderEnd();
	
	void DrawTabs();
private:
	GLuint m_vao;
};

#endif // !EDITOR_UI_H
