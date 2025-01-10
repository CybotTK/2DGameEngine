#ifndef VIEWPORT_TAB_H
#define VIEWPORT_TAB_H

#include "Editor/EditorTab.h"

class EditorUI;

class ViewportTab : public EditorTab {
public:
	ViewportTab(EditorUI* editor);
	virtual ~ViewportTab();

	virtual void DrawUI() override;

	EditorUI* m_editorUI = nullptr;
};

#endif // !VIEWPORT_TAB_H
