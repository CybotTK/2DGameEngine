#include "Core/Scene.h"

#include "Engine.h"

#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Graphics.h"

Scene::Scene()
{
	//Creating the physics world:
	m_physicsWorld = new b2World(b2Vec2(0.f, -10.f));

	// Testing testing 
	{
		auto layer1 = new Layer(this, "Layer1");
		auto layer2 = new Layer(this, "Layer2");
		layer2->tint = { 1.f, 0., 0., 1.0f };
		layer2->useCamera = false;

		auto layer3 = new Layer(this, "SimulationLayer");

		// The order we add will also define the render order
		layers.push_back(layer2);
		layers.push_back(layer1);
		layers.push_back(layer3);

		// Layer1 Objects
		auto root1 = new GameObject();
		root1->physics.type = GameObject::DYNAMIC;
		root1->sprite.texture.Set("test.png");
		root1->position = { -1.f, 0.f };
		root1->rotation = 25.f;

		auto root1Child = new GameObject();
		root1Child->physics.type = GameObject::GHOST;
		root1Child->SetParent(root1);
		root1Child->sprite.color = { 1.f,0.f,0.f,1.f };
		root1Child->position = { 1.f, 1.f };
		root1Child->scale = { 0.2f, 0.2f };
		root1Child->rotation = 45.f;

		layer1->Add(root1);

		// Layer2 Objects (The Background)
		auto obj3 = new GameObject();
		obj3->physics.type = GameObject::GHOST;
		obj3->sprite.texture.Set("test.png");
		layer2->Add(obj3);

		//Simulation Layer Object
		auto ground = new GameObject();
		auto box = new GameObject();

		ground->scale = { 10.f, 2.f };
		ground->position = { 0.f, -5.f };

		box->position = { 3.f, 2.f };
		box->rotation = 32.f;
		box->physics.type = GameObject::DYNAMIC;
		box->physics.fixedRotation = true;

		layer3->Add(ground);
		layer3->Add(box);
	}
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

void Scene::UpdatePhysics()
{
	auto allObjects = GetObjectsRecursively();

	// First we update the transform in the physics world:
	for (auto obj : allObjects) {
		obj->SubmitTransformToPhysicsWorld();
	}

	// Now we step it
	m_physicsWorld->Step(0.01, 6, 2);

	// We get transform back to be renderd and run in the logic step
	for (auto obj : allObjects) {
		if (obj->physics.type == GameObject::DYNAMIC) {
			obj->RetrieveTransformFromPhysicsWorld();
		}
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

b2World* Scene::GetBox2DWorld() const
{
	return m_physicsWorld;
}

std::vector<GameObject*> Scene::GetObjectsRecursively()
{
	std::vector<GameObject*> out;

	for (auto layer : layers) {
		auto rec = layer->GetObjectsRecursively();
		out.insert(out.end(), rec.begin(), rec.end());
	}

	return out;
}

glm::vec2 Scene::GetGravity()
{
	auto gravity = m_physicsWorld->GetGravity();
	return {gravity.x, gravity.y};
}

void Scene::SetGravity(glm::vec2 value)
{
	SetGravity(value.x, value.y);
}

void Scene::SetGravity(float x, float y)
{
	m_physicsWorld->SetGravity(b2Vec2(x,y));
}


