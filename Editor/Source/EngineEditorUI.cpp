#include "EngineEditorUI.h"

#include "Editor/Tabs/ViewportTab.h"
#include "Tabs/HierarchyTab.h"

EngineEditorUI::EngineEditorUI() {
	// Testing:
	tabs.push_back(new HierarchyTab());
	tabs.push_back(new ViewportTab(this));
	tabs.push_back(new EditorTab("Tab 2"));
	tabs.push_back(new EditorTab("Tab 3"));
	tabs.push_back(new EditorTab("Tab 4"));
}

EngineEditorUI::~EngineEditorUI() {
}
