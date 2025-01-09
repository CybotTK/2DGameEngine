#ifndef EDITOR_UI_H
#define EDITOR_UI_H

#include "Graphics/FrameBuffer.h"

class EditorUI {
public:
	EditorUI();
	virtual ~EditorUI();

	void Update();
	void Draw();

	FrameBuffer viewport;
protected:
	void RenderBegin();
	void Render();
	void RenderEnd();
	
	void DrawTabs();
private:
	GLuint m_vao;
};

#endif // !EDITOR_UI_H
