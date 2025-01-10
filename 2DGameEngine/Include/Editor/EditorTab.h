#ifndef EDITOR_UI_TAB_H
#define EDITOR_UI_TAB_H

#include <string>

class EditorTab {
public:
	EditorTab();
	EditorTab(const std::string& tabName);
	virtual ~EditorTab();

	//Returns true if tab is hovered
	bool DrawTab();

	//Draws the contect of the tab
	virtual void DrawUI();

	bool active = true;
	std::string name = "Editor Tab";
protected:
	int m_flags = 0;
};

#endif // !EDITOR_UI_TAB_H
