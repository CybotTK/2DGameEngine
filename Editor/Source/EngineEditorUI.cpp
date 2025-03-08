#include "EngineEditorUI.h"

#include "Editor/Tabs/ViewportTab.h"

#include "Tabs/HierarchyTab.h"
#include "Tabs/DetailsTab.h"
#include "Tabs/ResourceTab.h"

#include "Engine.h"

#include "System/Dialogs.h"

#include <iostream>

EngineEditorUI::EngineEditorUI() {
	m_useMenuBar = true;

	tabs.push_back(new HierarchyTab());
	tabs.push_back(new ViewportTab(this));
	tabs.push_back(new DetailsTab());
	tabs.push_back(new ResourceTab());
}

EngineEditorUI::~EngineEditorUI() {
}

void EngineEditorUI::Update() {
	auto app = App::Get();

	if (app->input.Active(InputKey::KEY_LEFT_CTRL)) {
		if (app->input.Pressed(InputKey::KEY_N)) {
			RunNewProject();
		}
		if (app->input.Pressed(InputKey::KEY_S)) {
			RunSaveProject();
		}
		if (app->input.Pressed(InputKey::KEY_O)) {
			RunLoadProject();
		}
	}

	if (ImGui::BeginMainMenuBar()) {

		if (ImGui::BeginMenu("File...")) {
			if (ImGui::MenuItem("New", "Ctrl + N")) {
				RunNewProject();
			}
			ui::Separator();
			if (ImGui::MenuItem("Save", "Ctrl + S")) {
				RunSaveProject();
			}
			if (ImGui::MenuItem("Load", "Ctrl + O")) {
				RunLoadProject();
			}
			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Project Settings")) {
			selected = &m_projectSettings;
		}

		ImGui::EndMainMenuBar();
	}
}

void EngineEditorUI::RunNewProject() {
	auto app = App::Get();

	if (dialogs::QuestionMessage("Create a New Project",
		"All unsaved progess will be lost! Continue?")) {
		if (saveFile != "") {
			if (dialogs::QuestionMessage("Save current Project?",
				"Do you want to save your current project first? All unsaved progess will be lost!")) {
				RunSaveProject();
			}
		}

		app->NewProject();
	}
}

void EngineEditorUI::RunSaveProject() {
	auto app = App::Get();

	if (saveFile == "") {
		saveFile = dialogs::SaveFile("Save Project As...", { "Engine Project", "*" });
	}

	if (saveFile != "") {
		File file(saveFile, File::WRITE);
		app->Save(&file);
	}
}

void EngineEditorUI::RunLoadProject() {
	auto app = App::Get();

	if (saveFile != "") {
		if (dialogs::QuestionMessage("Save current Project?", 
			"Do you want to save your current project first? All unsaved progess will be lost!")){
			RunSaveProject();
		}
	}
	auto loadFile = dialogs::OpenFile("Load Project...", { "Engine Project", "*" }, false);
	if (loadFile.size() == 1) {
		saveFile = loadFile[0];

		File file(saveFile, File::READ);
		app->Load(&file);
	}
}
