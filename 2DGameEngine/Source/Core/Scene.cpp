#include "Core/Scene.h"

#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"

Scene::Scene()
{
	// Testing testing
	auto obj1 = new GameObject();
	//obj1->sprite.color = { 1.f,0.f,0.f,1.f };
	obj1->sprite.texture.Set("test.png");
	obj1->position = { -1.f, 0.f };
	obj1->rotation = 70.f;
	objects.push_back(obj1);

	auto obj2 = new GameObject();
	obj2->sprite.color = { 1.f,0.f,0.f,1.f };
	obj2->SetParent(obj1);
	obj2->position = { 2.f, 2.f };
	obj2->rotation = 45.f;
	obj2->scale = { 0.2f, 0.2f };
	objects.push_back(obj2);

}

Scene::~Scene()
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

void Scene::Update()
{
	for (auto obj : objects)
	{
		obj->Update();
	}
}

void Scene::Draw(Shader* shader, float aspect)
{
	shader->Use();

	//Camera view projection
	shader->Set("viewProjection", camera.GetViewProjection(aspect));

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
