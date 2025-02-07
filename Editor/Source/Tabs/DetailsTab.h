#ifndef DETAILS_TAB_H
#define DETAILS_TAB_H

#include "Editor/EditorTab.h"

class DetailsTab : public EditorTab {
public:
	DetailsTab();
	virtual ~DetailsTab();

	virtual void DrawUI() override;
};

#endif // !DETAILS_TAB_H
