#include "Tabs/HierarchyTab.h"

#include "Engine.h"

#include "Editor/UI/Props.h"

#include "Editor/ImGui/imgui.h"

HierarchyTab::HierarchyTab() {
	name = "Hierarchy";
}

HierarchyTab::~HierarchyTab() {
}

void HierarchyTab::DrawUI() {
	auto app = App::Get();
	auto scene = app->GetCurrentScene();
	auto editor = app->GetEditor();

	if (!scene) {
		ui::Text("No Scene selected!");
		return;
	}

	int headerFlags = 0;
	headerFlags |= ImGuiTreeNodeFlags_AllowItemOverlap;
	headerFlags |= ImGuiTreeNodeFlags_CollapsingHeader;	
	headerFlags |= ImGuiTreeNodeFlags_OpenOnArrow;
	headerFlags |= ImGuiTreeNodeFlags_DefaultOpen;

	for (auto layer : scene->layers) {
		int flags = headerFlags;
		if (layer == editor->selected) {
			flags |= ImGuiTreeNodeFlags_Selected;
		}

		ui::PushID(layer);
		if (ImGui::TreeNodeEx(layer->name.c_str(), flags)) {
			if (ImGui::IsItemClicked()) {
				editor->selected = layer;
			}

			for (auto obj : layer->objects) {
				if (obj->GetParent() == nullptr) {
					DrawObject(obj);
				}
			}
		}
		ui::PopID();
	}

}

void HierarchyTab::DrawObject(GameObject* obj) {
	auto app = App::Get();
	auto editor = app->GetEditor();

	auto children = obj->GetChildren(false);

	int flags = 0;
	flags |= ImGuiTreeNodeFlags_AllowItemOverlap;
	flags |= ImGuiTreeNodeFlags_DefaultOpen;
	flags |= ImGuiTreeNodeFlags_OpenOnArrow;
	flags |= ImGuiTreeNodeFlags_FramePadding;

	if (children.size() == 0) {
		flags |= ImGuiTreeNodeFlags_Leaf;
		//flags |= ImGuiTreeNodeFlags_Bullet;
	}

	if (obj == editor->selected) {
		flags |= ImGuiTreeNodeFlags_Selected;
	}

	ui::PushID(obj);
	if (ImGui::TreeNodeEx(obj->name.c_str(), flags)) {
		if (ImGui::IsItemClicked()) {
			editor->selected = obj;
		}

		for (auto child : children) {
			DrawObject(child);
		}

		ImGui::TreePop();
	}

	ui::PopID();
}
