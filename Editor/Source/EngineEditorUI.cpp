#include "EngineEditorUI.h"

#include "Editor/Tabs/ViewportTab.h"

EngineEditorUI::EngineEditorUI() {
	// Testing:
	tabs.push_back(new EditorTab("Tab 1"));
	tabs.push_back(new EditorTab("Tab 2"));
	tabs.push_back(new EditorTab("Tab 3"));
	tabs.push_back(new EditorTab("Tab 4"));
	tabs.push_back(new ViewportTab(this));
}

EngineEditorUI::~EngineEditorUI() {
}
