#include "Tabs/ResourceTab.h"

#include "Editor/UI/Props.h"
#include "Editor/ImGui/imgui.h"

#include "Engine.h"

ResourceTab::ResourceTab() {
	name = "Resources";
}

ResourceTab::~ResourceTab() {
}

#define DRAW_MAP(NAME, MAP, EXTRAS)									\
	if (ImGui::BeginTabItem(NAME)) {						\
		for (auto obj : MAP) {								\
			if (obj.second.asset->DrawIcon()) {				\
				editor->selected = obj.second.asset;		\
			}												\
		}													\
		EXTRAS												\
		ImGui::EndTabItem();								\
	}														\

void ResourceTab::DrawUI()  {
	auto app = App::Get();
	auto editor = app->GetEditor();

	/*if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Import...")) {
			if (ImGui::MenuItem("Image")) {

			}
			if (ImGui::MenuItem("Audio")) {

			}

			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("NewScene")) {

		}

		ImGui::EndMainMenuBar();
	}
	Trying to add a menu bar
	*/

	if (ImGui::BeginTabBar("##ResourcesTab")) {
		DRAW_MAP("Images", app->data.images, {});
		DRAW_MAP("Audios", app->data.audios, {});
		DRAW_MAP("Scenes", app->data.scenes, {});

		//DRAW_MAP("Meshes", app->data.meshes, {});

		ImGui::EndTabBar();
	}

}
