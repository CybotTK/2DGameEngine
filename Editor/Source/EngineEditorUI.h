#ifndef ENGINE_EDITOR_UI_H
#define ENGINE_EDITOR_UI_H

#include "Editor/EditorUI.h"
#include "Mocks/ProjectSettings.h"

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

	void RunExportGame();

	ProjectSettings m_projectSettings;
};

#endif // !ENGINE_EDITOR_UI_H
