#include "Tabs/ResourceTab.h"

#include "Editor/UI/Props.h"
#include "Editor/ImGui/imgui.h"

#include "System/Dialogs.h"

#include "Engine.h"

ResourceTab::ResourceTab() {
	name = "Resources";
}

ResourceTab::~ResourceTab() {
}

template <typename T>
void DrawMapUI(const std::string& name, T& MAP) {
	auto app = App::Get();
	auto editor = app->GetEditor();

	if (ImGui::BeginTabItem(name.c_str())) {
		std::vector<size_t> toRemove;
		for (auto obj : MAP) {
			bool isHovered = false;
			if (obj.second.asset->DrawIcon(&isHovered)) {
				editor->selected = obj.second.asset;
			}
			std::string aID = std::to_string((size_t)obj.second.asset);
				if (isHovered) {
					if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
						ImGui::OpenPopup(aID.c_str());
					}
				}
			if (ImGui::BeginPopup(aID.c_str())) {
				if (ImGui::MenuItem("Delete")) {
					toRemove.push_back(obj.first);
				}
				ImGui::EndPopup();
			}
		}
		for (auto obj : toRemove) {
			MAP.Remove(obj);
		}
		ImGui::EndTabItem();
	}
}

void ResourceTab::DrawUI()  {
	auto app = App::Get();
	auto editor = app->GetEditor();

	if (ImGui::Button("New Scene")) {
		auto scene = new Scene();
		scene->AddDefaultObjects();
		app->data.scenes.Add("Scene " + std::to_string(app->data.scenes.size()), scene);
		editor->selected = scene;
	}
	ui::SameLine();
	if (ui::Button("Import...")) {
		ImGui::OpenPopup("ImportPopup");
	}
	ui::SameLine();
	if (ImGui::Button("New Script")) {
		auto script = new PythonScript();
		app->data.scripts.Add("Script " + std::to_string(app->data.scripts.size()), script);
		editor->selected = script;
	}

	if (ImGui::BeginPopup("ImportPopup")) {
		if (ImGui::MenuItem("Image...")) {	
			auto results = dialogs::OpenFile(
				"Import Image Resource",
				{ "Images (.png .jpg)", "*.png *.jpg" }
			);

			for (auto res : results) {
				auto img = new ImageTexture(res);
				app->data.images.Add(res, img);
			}
		}
		if (ImGui::MenuItem("Audio...")) {	
			auto results = dialogs::OpenFile(
				"Import Audio Resource",
				{ "Audios (.mp3 .ogg .wav)", "*.mp3 *.ogg *.wav" }
			);

			for (auto res : results) {
				auto audio = new AudioTrack(res);
				app->data.audios.Add(res, audio);
			}
		}															
		ImGui::EndPopup();											
	}

	ui::Separator();

	if (ImGui::BeginTabBar("##ResourcesTab")) {
		DrawMapUI("Scenes", app->data.scenes);
		DrawMapUI("Images", app->data.images);
		DrawMapUI("Audios", app->data.audios);
		DrawMapUI("Script", app->data.scripts);

		//DrawMapUI("Meshes", app->data.meshes);

		ImGui::EndTabBar();
	}

}
