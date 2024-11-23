#include "Core/Scene.h"

#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Graphics.h"

Scene::Scene()
{
	// Testing testing 
	auto layer1 = new Layer("Layer1");

	auto layer2 = new Layer("Layer2");
	layer2->tint = { 1.f, 0., 0., 0.8f };
	layer2->useCamera = false;

	// The order we add will also define the render order
	layers.push_back(layer2);
	layers.push_back(layer1);

	// Layer1 Objects
	auto root1 = new GameObject();
	root1->sprite.texture.Set("test.png");
	root1->position = { -1.f, 0.f };
	root1->rotation = 70.f;

	auto root1Child = new GameObject();
	root1Child->SetParent(root1); 
	root1Child->sprite.color = { 1.f,0.f,0.f,1.f };
	root1Child->position = { 2.f, 2.f };
	root1Child->rotation = 45.f;
	root1Child->scale = { 0.2f, 0.2f };

	layer1->Add(root1);

	// Layer2 Objects
	auto obj3 = new GameObject();
	obj3->sprite.texture.Set("test.png");
	layer2->Add(obj3);
}

Scene::~Scene()
{
	for (auto layer : layers)
	{
		delete layer;
	}
	layers.clear();
}

void Scene::Update()
{
	for (auto layer : layers)
	{
		layer->Update();
	}
}

void Scene::Draw(Shader* shader, float aspect)
{
	// Background color setter
	graphics::ClearBuffers(background.x, background.y, background.z, 1.f);

	shader->Use();

	// We draw each layer
	for (auto layer : layers)
	{
		layer->Draw(camera, shader, aspect);
	}
}
