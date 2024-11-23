#include "Core/Layer.h"

#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Graphics.h"

Layer::Layer(const std::string& layerName) : name(layerName)
{
}

Layer::~Layer()
{
	for (auto obj : objects)
	{
		if (obj->GetParent() == nullptr)
		{
			delete obj;
		}
	}
	objects.clear();
}

void Layer::Update()
{
	for (auto obj : objects)
	{
		obj->Update();
	}
}

void Layer::Draw(const Camera& camera, Shader* shader, float aspect)
{
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
		assert(lastMesh);
		obj->Draw(shader, lastMesh);
	}
}

void Layer::Add(GameObject* object)
{
	object->SetLayer(this);
}

void Layer::Remove(GameObject* object)
{
	auto it = std::find(objects.begin(), objects.end(), object);
	assert(it != objects.end()); // Make sure we found the GameObject
	objects.erase(it);
}
