#ifndef HIERARCHY_TAB_H
#define HIERARCHY_TAB_H

#include "Editor/EditorTab.h"

class HierarchyTab : public EditorTab {
public:
	HierarchyTab();
	virtual ~HierarchyTab();

	virtual void DrawUI() override;
};

#endif // !HIERARCHY_TAB_H
