#ifndef EDITOR_UI_H
#define EDITOR_UI_H

#include "Editor/EditorTab.h"
#include "Graphics/FrameBuffer.h"

#include "Asset/Object.h"

class EditorUI {
public:
	EditorUI();
	virtual ~EditorUI();

	void UpdateAll();
	void Draw();

	virtual void Update();

	FrameBuffer viewport;
	std::vector<EditorTab*> tabs;

	Object* selected = nullptr;
protected:
	void RenderBegin();
	void Render();
	void RenderEnd();
	
	void DrawTabs();

	bool m_useMenuBar = false;
};

#endif // !EDITOR_UI_H
