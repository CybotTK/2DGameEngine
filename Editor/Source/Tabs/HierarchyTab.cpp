#include "Tabs/HierarchyTab.h"

#include "Engine.h"

#include "Editor/UI/Props.h"

#include "Editor/ImGui/imgui.h"

HierarchyTab::HierarchyTab() {
	name = "Hierarchy";
}

HierarchyTab::~HierarchyTab() {
}

static GameObject*	__dndGameObject = nullptr;
static Layer*		__dndLayer		= nullptr;

void HierarchyTab::DrawUI() {
	auto app = App::Get();
	auto scene = app->GetCurrentScene();
	auto editor = app->GetEditor();

	if (!scene) {
		ui::Text("No Scene selected!");
		return;
	}

	if (ui::Button("New Layer", {ui::GetRemainingWidth(), 0.f})) {
		Layer* newLayer = new Layer(scene, "Layer" + std::to_string(scene->layers.size()));
		scene->layers.push_back(newLayer);
	}

	ui::Separator();

	ImGui::BeginChild("HierarchyTabList");
	DrawLayers();
	ImGui::EndChild();
}

void HierarchyTab::DrawLayers() {
	auto app = App::Get();
	auto scene = app->GetCurrentScene();
	auto editor = app->GetEditor();

	int headerFlags = 0;
	headerFlags |= ImGuiTreeNodeFlags_AllowItemOverlap;
	headerFlags |= ImGuiTreeNodeFlags_CollapsingHeader;
	headerFlags |= ImGuiTreeNodeFlags_OpenOnArrow;
	headerFlags |= ImGuiTreeNodeFlags_DefaultOpen;

	std::vector<Layer*> toRemoveLayers;
	for (auto layer : scene->layers) {
		bool abortIteration = false;

		int flags = headerFlags;
		if (layer == editor->selected) {
			flags |= ImGuiTreeNodeFlags_Selected;
		}

		ui::PushID(layer);

		// Drag and Drop : Source
		{
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
				__dndLayer = layer;

				ImGui::SetDragDropPayload("DND_Layer", nullptr, 0);
				{
					ui::Text(layer->debug.name);
				}
				ImGui::EndDragDropSource();
			}
		}

		// Drag and Drop : Target
		{
			if (ImGui::BeginDragDropTarget()) {
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_GameObject")) {
					GameObject* gameObject = __dndGameObject;

					if (gameObject->GetParent()) {
						gameObject->RemoveParent();
					}
					gameObject->SetLayer(layer);

				}
				ImGui::EndDragDropTarget();
			}
			if (ImGui::BeginDragDropTarget()) {
				bool hasBeenMoved = false;
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_Layer")) {
					Layer* dndLayer = __dndLayer;

					if (dndLayer == layer) {
						hasBeenMoved = true;
						dndLayer->MoveDown();
					}
					if (dndLayer->GetLayerIndex() > layer->GetLayerIndex() && !hasBeenMoved) {
						hasBeenMoved = true;
						while (dndLayer->GetLayerIndex() > layer->GetLayerIndex()) {
							dndLayer->MoveUp();
						}
					}
					if (dndLayer->GetLayerIndex() < layer->GetLayerIndex() && !hasBeenMoved) {
						while (dndLayer->GetLayerIndex() < layer->GetLayerIndex()) {
							dndLayer->MoveDown();
						}
					}

					//You can't keep iterating the layer list if you change them
					abortIteration = true;
				}
				ImGui::EndDragDropTarget();
			}
		}

		// RightClick panel
		{
			if (ImGui::IsItemHovered()) {
				if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
					ImGui::OpenPopup("##Layer");
				}
			}
			if (ImGui::BeginPopup("##Layer")) {
				if (ImGui::MenuItem("Delete")) {
					abortIteration = true;
					toRemoveLayers.push_back(layer);
				}
				ImGui::EndPopup();
			}
		}

		ui::SameLine();

		ui::SetCursorX(ui::GetWidth() - 90.f);
		if (ui::Button("Add New Object")) {
			auto obj = new GameObject();
			obj->debug.name += " " + std::to_string(layer->objects.size());
			layer->Add(obj);
			editor->selected = obj;
		}

		if (ImGui::TreeNodeEx(layer->debug.name.c_str(), flags)) {
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

		if (abortIteration) {
			break;
		}
	}

	for (auto layer : toRemoveLayers) {
		auto it = std::find(scene->layers.begin(), scene->layers.end(), layer);
		scene->layers.erase(it);
		delete layer;
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
	auto out = ImGui::TreeNodeEx(obj->debug.name.c_str(), flags);

	// Drag and Drop : Source
	{
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
			__dndGameObject = obj;

			ImGui::SetDragDropPayload("DND_GameObject", nullptr, 0);
			{
				ui::Text(obj->debug.name);
			}
			ImGui::EndDragDropSource();
		}
	}

	// Drag and Drop : Target
	{
		if (ImGui::BeginDragDropTarget()) {
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_GameObject")) {
				GameObject* gameObject = __dndGameObject;
				if (gameObject == obj) {
					gameObject->RemoveParent();
				}
				else if (gameObject->GetParent() == obj) {
					gameObject->RemoveParent();
				}
				else {
					//gameObject->GetLayer()->Remove(gameObject);
					gameObject->SetParent(obj);
				}
			}
			ImGui::EndDragDropTarget();
		}
	}

	// RightClick panel
	{
		if (ImGui::IsItemHovered()) {
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
				ImGui::OpenPopup("##GameObject");
			}
		}
		if (ImGui::BeginPopup("##GameObject")) {
			if (ImGui::MenuItem("Delete")) {
				obj->deletedInEditor = true;
				obj->Kill();
			}
			ImGui::EndPopup();
		}
	}

	if (ImGui::IsItemClicked()) {
		editor->selected = obj;
	}

	if (out) {
		for (auto child : children) {
			DrawObject(child);
		}

		ImGui::TreePop();
	}

	ui::PopID();
}
