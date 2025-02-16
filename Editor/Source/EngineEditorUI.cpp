#include "EngineEditorUI.h"

#include "Editor/Tabs/ViewportTab.h"

#include "Tabs/HierarchyTab.h"
#include "Tabs/DetailsTab.h"
#include "Tabs/ResourceTab.h"

EngineEditorUI::EngineEditorUI() {
	// Testing:
	tabs.push_back(new HierarchyTab());
	tabs.push_back(new ViewportTab(this));
	tabs.push_back(new DetailsTab());
	tabs.push_back(new ResourceTab());
}

EngineEditorUI::~EngineEditorUI() {
}
