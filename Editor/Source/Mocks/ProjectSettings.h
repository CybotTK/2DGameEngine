#ifndef PROJECT_SETTINGS_H
#define PROJECT_SETTINGS_H

#include "Asset/Object.h"

class ProjectSettings : public Object {
public:
	ProjectSettings();
	virtual ~ProjectSettings();

	virtual void DrawUI() override;
};

#endif // !PROJECT_SETTINGS_H