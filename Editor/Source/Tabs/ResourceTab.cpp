#include "Tabs/ResourceTab.h"

#include "Editor/UI/Props.h"
#include "Editor/ImGui/imgui.h"

#include "Engine.h"

ResourceTab::ResourceTab() {
	name = "Resources";
}

ResourceTab::~ResourceTab() {
}

#define DRAW_MAP(NAME, MAP, EXTRAS)												\
	if (ImGui::BeginTabItem(NAME)) {											\
		std::vector<size_t> toRemove;											\
		for (auto obj : MAP) {													\
			bool isHovered = false;												\
			if (obj.second.asset->DrawIcon(&isHovered)) {						\
				editor->selected = obj.second.asset;							\
			}																	\
			{																	\
				std::string aID = std::to_string((size_t)obj.second.asset);		\
				if (isHovered) {												\
					if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {		\
						ImGui::OpenPopup(aID.c_str());									\
					}															\
				}																\
				if (ImGui::BeginPopup(aID.c_str())) {									\
					if (ImGui::MenuItem("Delete")) {							\
						toRemove.push_back(obj.first);							\
					}															\
					ImGui::EndPopup();											\
				}																\
			}																	\
		}																		\
		for (auto obj : toRemove) {												\
			MAP.Remove(obj);													\
		}																		\
		EXTRAS																	\
		ImGui::EndTabItem();													\
	}																			\

void ResourceTab::DrawUI()  {
	auto app = App::Get();
	auto editor = app->GetEditor();

	if (ImGui::Button("New Scene")) {
		auto scene = new Scene();
		app->data.scenes.Add("Scene " + std::to_string(app->data.scenes.size()), scene);
		editor->selected = scene;
	}
	ui::SameLine();
	if (ui::Button("Import...")) {

	}

	if (ImGui::BeginTabBar("##ResourcesTab")) {
		DRAW_MAP("Images", app->data.images, {});
		DRAW_MAP("Audios", app->data.audios, {});
		DRAW_MAP("Scenes", app->data.scenes, {});

		//DRAW_MAP("Meshes", app->data.meshes, {});

		ImGui::EndTabBar();
	}

}
