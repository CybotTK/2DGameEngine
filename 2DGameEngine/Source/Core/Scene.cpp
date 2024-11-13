#include "Core/Scene.h"

#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"

Scene::Scene()
{
	m_plane = Mesh::CreatePlane();

	// Testing testing
	auto obj1 = new GameObject();
	obj1->sprite.color = { 1.f,0.f,0.f,1.f };
	obj1->position = { -1.f, 0.f };
	obj1->rotation = 70.f;
	objects.push_back(obj1);

	auto obj2 = new GameObject();
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

	delete m_plane;
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

	m_plane->Use();

	for (auto obj : objects)
	{
		obj->Draw(shader, m_plane);
	}
}
