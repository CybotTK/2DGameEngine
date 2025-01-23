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

	if (!scene) {
		ui::Text("No Scene selected!");
		return;
	}

	int headerFlags = 0;
	headerFlags |= ImGuiTreeNodeFlags_AllowItemOverlap;
	headerFlags |= ImGuiTreeNodeFlags_CollapsingHeader;
	headerFlags |= ImGuiTreeNodeFlags_DefaultOpen;

	for (auto layer : scene->layers) {
		ui::PushID(layer);
		if (ImGui::TreeNodeEx(layer->name.c_str(), headerFlags)) {
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
	ui::PushID(obj);

	auto children = obj->GetChildren(false);

	int flags = 0;
	flags |= ImGuiTreeNodeFlags_AllowItemOverlap;
	flags |= ImGuiTreeNodeFlags_DefaultOpen;
	flags |= ImGuiTreeNodeFlags_OpenOnArrow;

	if (children.size() == 0) {
		flags |= ImGuiTreeNodeFlags_Leaf;
		//flags |= ImGuiTreeNodeFlags_Bullet;
	}

	if (ImGui::TreeNodeEx(obj->name.c_str(), flags)) {
		for (auto child : children) {
			DrawObject(child);
		}

		ImGui::TreePop();
	}

	ui::PopID();
}
