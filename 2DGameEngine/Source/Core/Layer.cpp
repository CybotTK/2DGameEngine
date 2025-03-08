#include "Core/Layer.h"

#include "Core/Scene.h"

#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Graphics.h"

#include "Editor/UI/Props.h"

Layer::Layer(Scene* scene, const std::string& layerName) {
	debug.name = layerName;
	m_scene = scene;
}

Layer::~Layer() {
	for (auto obj : objects)
	{
		if (obj->GetParent() == nullptr)
		{
			delete obj;
		}
	}
	objects.clear();
}

void Layer::Save(File* file) {
	Object::Save(file);

	file->Write(tint);
	file->Write(useCamera);

	file->Write(objects.size());
	for (auto obj : objects) {
		obj->Save(file);
	}
}

void Layer::Load(File* file) {
	Object::Load(file);

	file->Read(tint);
	file->Read(useCamera);

	size_t count;
	file->Read(count);
	for (size_t i = 0; i < count; i++) {
		auto obj = new GameObject();
		obj->Load(file);
		Add(obj);
	}
}

void Layer::Update() {
	for (auto obj : objects)
	{
		if (!obj->IsInitialized()) {
			obj->Initialize(m_scene);
		}
		obj->Update();
	}
}

void Layer::Draw(const Camera& camera, Shader* shader, float aspect) {
	if (useCamera) {
		//Camera view projection
		shader->Set("viewProjection", camera.GetViewProjection(aspect));
	}
	else {
		shader->Set("viewProjection", glm::mat4(1));
	}

	shader->Set("layer.tint", tint);

	// Drawing the GameObjects;
	size_t lastID = 0;
	Mesh* lastMesh = nullptr;
	for (auto obj : objects)
	{
		if (obj->sprite.shape.GetID() != lastID) {
			lastID = obj->sprite.shape.GetID();
			lastMesh = obj->sprite.shape.Get();
			lastMesh->Use();
		}
		if (lastMesh) {
			obj->Draw(shader, lastMesh);
		}
	}
}

GameObject* Layer::NewObject() {
	auto obj = new GameObject();
	Add(obj);
	return obj;
}

void Layer::DrawUI() {
	ui::ObjectHeader(&debug.name, "Layer");

	ui::PropColor("Tint", &tint);
	ui::Prop("Use Camera", &useCamera);

	if (ui::Header("Layer Order", false)) {
		int indx = GetLayerIndex();

		ui::PropText("Current Index", std::to_string(indx + 1) + "/" + std::to_string(m_scene->layers.size()));

		ui::Separator();

		if (ui::Button("Move up", { ui::GetRemainingWidth(), 0.f })) {
			MoveUp();
		}
		if (ui::Button("Move down", { ui::GetRemainingWidth(), 0.f })) {
			MoveDown();
		}
	}
}

void Layer::Add(GameObject* object) {
	object->SetLayer(this);
}

void Layer::Remove(GameObject* object) {
	auto it = std::find(objects.begin(), objects.end(), object);
	if (it != objects.end()) { // Make sure we found the GameObject
		objects.erase(it);
	}
}

int Layer::GetLayerIndex() {
	int pos = 0;
	for (auto layer : m_scene->layers) {
		if (layer == this) { break; }
		pos++;
	}
	if (pos == m_scene->layers.size()) {
		return -1;
	}
	return pos;
}

void Layer::MoveUp() {
	int indx = GetLayerIndex();

	if (indx > 0) {
		m_scene->layers[indx] = m_scene->layers[indx - 1];
		m_scene->layers[indx - 1] = this;
	}
}

void Layer::MoveDown() {
	int indx = GetLayerIndex();

	if (indx < m_scene->layers.size() - 1) {
		m_scene->layers[indx] = m_scene->layers[indx + 1];
		m_scene->layers[indx + 1] = this;
	}
}

void Layer::CleanupObjectList() {
	std::vector<GameObject*> toRemove;

	for (auto obj : objects) {
		if (obj->GetParent() != nullptr) {
			toRemove.push_back(obj);
		}
	}
	for (auto obj : toRemove) {
		auto it = std::find(objects.begin(), objects.end(), obj);
		objects.erase(it);
	}
	toRemove.clear();
}

std::vector<GameObject*> Layer::GetObjectsRecursively() {
	std::vector<GameObject*> out = objects;

	for (auto obj : objects) {
		auto rec = obj->GetChildren(true);
		out.insert(out.end(), rec.begin(), rec.end());
	}

	return out;
}
