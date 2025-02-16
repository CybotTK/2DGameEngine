#ifndef RESOURCE_TAB_H
#define RESOURCE_TAB_H

#include "Editor/EditorTab.h"

class ResourceTab : public EditorTab {
public:
	ResourceTab();
	virtual ~ResourceTab();

	virtual void DrawUI() override;
};

#endif // !RESOURCE_TAB_H
