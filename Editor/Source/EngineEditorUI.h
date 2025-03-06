#ifndef ENGINE_EDITOR_UI_H
#define ENGINE_EDITOR_UI_H

#include "Editor/EditorUI.h"

class EngineEditorUI : public EditorUI {
public:
	EngineEditorUI();
	virtual ~EngineEditorUI();

	virtual void Update() override;

	std::string saveFile = "";

protected:
	void RunNewProject();

	void RunSaveProject();
	void RunLoadProject();
};

#endif // !ENGINE_EDITOR_UI_H
