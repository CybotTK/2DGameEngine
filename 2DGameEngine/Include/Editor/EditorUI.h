#ifndef EDITOR_UI_H
#define EDITOR_UI_H

#include "System/Window.h"
#include "System/Input.h"

class EditorUI {
public:
	EditorUI();
	virtual ~EditorUI();

	void Update();
	void Draw();

protected:
	void RenderBegin();
	void Render();
	void RenderEnd();
	
	void DrawTabs();
private:
	GLuint m_vao;
};

#endif // !EDITOR_UI_H
