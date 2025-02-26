#ifndef HIERARCHY_TAB_H
#define HIERARCHY_TAB_H

#include "Editor/EditorTab.h"

class GameObject;

class HierarchyTab : public EditorTab {
public:
	HierarchyTab();
	virtual ~HierarchyTab();

	virtual void DrawUI() override;
private:
	void DrawLayers();
	void DrawObject(GameObject* obj);
};

#endif // !HIERARCHY_TAB_H
