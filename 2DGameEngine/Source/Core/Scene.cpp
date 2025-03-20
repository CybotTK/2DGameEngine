#include "Core/Scene.h"

#include "Engine.h"

#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Graphics.h"

#include "Editor/UI/Props.h"

Scene::Scene() {
	//Creating the physics world:
	m_physicsWorld = new b2World(b2Vec2(0.f, -10.f));
}

Scene::~Scene() {
	auto app = App::Get();

	if (app->GetCurrentScene() == this) {
		app->SetCurrentScene(nullptr);
	}

	for (auto layer : layers) {
		delete layer;
	}
	layers.clear();
}

void Scene::AddDefaultObjects() {
	auto lBackground = new Layer(this, "Background");
	lBackground->useCamera = false;

	auto lGame = new Layer(this, "Simulation Layer");

	// The order we add will also define the render order
	layers.push_back(lBackground);
	layers.push_back(lGame);

	// lGame Objects
	auto box = new GameObject();
	box->debug.name = "Box";
	box->physics.type = GameObject::DYNAMIC;
	box->sprite.color = { 0.5f, 0.5f, 0.5f, 1.f };
	box->position = { -2.f, 3.f };
	box->rotation = 25.f;
	box->runLogic = true;

	box->constructionScript = R"(import engine

class MyComponent(engine.Component):
	def start(self):
		pass

	def update(self):
		owner = self.getOwner()
		input = engine.getApp().input

		if input.active(engine.KEY_A):
			print("KEY_A pressed!")
			owner.position.x -= 0.2 	

		if input.active(engine.KEY_D):
			print("KEY_D pressed!")
			owner.position.x += 0.2 

		if input.pressed(engine.KEY_SPACE):
			owner.position.y += 0.2 

# Adding component
object.components.append(MyComponent(object))
)";

	lGame->Add(box);

	// lBackground Objects
	auto obj3 = new GameObject();
	obj3->debug.name = "Background";
	obj3->physics.type = GameObject::GHOST;
	obj3->sprite.color = { 0.f, 0.58f, 1.f, 1.f };
	lBackground->Add(obj3);

	// Simulation Layer Object
	auto ground = new GameObject();
	ground->debug.name = "Ground";
	ground->sprite.color = { 0.1f, 0.1f, 0.1f, 1.f };
	ground->scale = { 10.f, 2.f };
	ground->position = { 0.f, -5.f };

	lGame->Add(ground);
}

void Scene::Save(File* file) {
	Object::Save(file);

	auto gravity = GetGravity();
	file->Write(gravity);

	file->Write(background);

	camera.Save(file);

	file->Write(layers.size());
	for (auto layer : layers) {
		layer->Save(file);
	}
}

void Scene::Load(File* file) {
	Object::Load(file);

	glm::vec2 gravity;
	file->Read(gravity);
	SetGravity(gravity);

	file->Read(background);

	camera.Load(file);

	// Makes sure this is a "blank" scene
	{
		for (auto layer : layers) {
			delete layer;
		}
		layers.clear();
	}

	size_t count;
	file->Read(count); 

	for (size_t i = 0; i < count; i++) {
		auto layer = new Layer(this);
		layer->Load(file);
		layers.push_back(layer);
	}
}

void Scene::DrawUI() {
	ui::ObjectHeader(&debug.name, "Scene");

	auto app = App::Get();
	app->SetCurrentScene(this);

	if (ui::Header("World")) {
		ui::PropColor("Background", &background);

		glm::vec2 gravity = GetGravity();
		ui::Prop("Gravity", &gravity);
		SetGravity(gravity);
	}

	if (ui::Header("Camera")) {
		ui::Prop("Position", &camera.position);
		ui::Prop("Rotation", &camera.rotation);
		ui::Prop("Scale", &camera.scale);

		ui::Separator();

		ui::Prop("Area", &camera.area);
	}
}

void Scene::Update() {
	for (auto layer : layers) {
		layer->Update();
	}
}

void Scene::UpdatePhysics(float deltaTime) {
	auto allObjects = GetObjectsRecursively();

	// First we update the transform in the physics world:
	for (auto obj : allObjects) {
		obj->SubmitTransformToPhysicsWorld();
	}

	// Now we step it
	m_physicsWorld->Step(deltaTime, 6, 2);

	// We get transform back to be renderd and run in the logic step
	for (auto obj : allObjects) {
		if (obj->physics.type == GameObject::DYNAMIC) {
			obj->RetrieveTransformFromPhysicsWorld();
		}
	}
}

void Scene::Draw(Shader* shader, float aspect) {
	// Background color setter
	graphics::ClearBuffers(background.x, background.y, background.z, 1.f);

	shader->Use();

	// We draw each layer
	for (auto layer : layers)
	{
		layer->Draw(camera, shader, aspect);
	}
}

void Scene::EndUpdate(){
	auto allObjects = GetObjectsRecursively();

	for (auto obj : allObjects) {
		if (obj->m_killed) {
			auto layer = obj->GetRoot()->GetLayer();

			assert(layer);
			layer->Remove(obj);

			delete obj;
		}
	}
}

b2World* Scene::GetBox2DWorld() const {
	return m_physicsWorld;
}

std::vector<GameObject*> Scene::GetObjectsRecursively() {
	std::vector<GameObject*> out;

	for (auto layer : layers) {
		auto rec = layer->GetObjectsRecursively();
		out.insert(out.end(), rec.begin(), rec.end());
	}

	return out;
}

glm::vec2 Scene::GetGravity() {
	auto gravity = m_physicsWorld->GetGravity();
	return {gravity.x, gravity.y};
}

void Scene::SetGravity(glm::vec2 value) {
	SetGravity(value.x, value.y);
}

void Scene::SetGravity(float x, float y) {
	m_physicsWorld->SetGravity(b2Vec2(x,y));
}
