#include "Core/GameObject.h"

#include "Engine.h"

#include "Core/Layer.h"

#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"

#include "Editor/UI/Props.h"
#include "Editor/ImGui/imgui.h"

GameObject::GameObject() {
	debug.name = "Game Object";
	sprite.shape.Set("Plane");
}

GameObject::~GameObject() {
	if (m_scene && m_physicsBody) {
		auto world = m_scene->GetBox2DWorld();

		world->DestroyBody(m_physicsBody);
	}

	for (auto child : m_children) {
		child->m_killed = true;
		child->RemoveParent();
	}
	m_children.clear();

	if (m_parent) {
		auto it = std::find(m_parent->m_children.begin(), m_parent->m_children.end(), this);
		if (it != m_parent->m_children.end()) {
			m_parent->m_children.erase(it);
		}
	}
}

void GameObject::DrawUI() {
	ui::ObjectHeader(&debug.name, "Game Object");

	if (ui::Header("Transform", true)) {
		ui::Prop("Position", &position);
		ui::Prop("Rotation", &rotation);
		ui::Prop("Scale", &scale);
	}

	if (ui::Header("Sprite", false)) {
		ui::PropColor("Color", &sprite.color);

		sprite.texture.DrawUI("Texture");
		// ATM commented
		//sprite.shape.DrawUI("Shape");
		//ui::Text("TO DO: IMPLEMENT TEXTURE AND SHAPE");
	}

	if (ui::Header("Physics", false)) {
		uiInternal::DrawPropPrefix("Type", "");
		std::string assetName = "";
		switch (physics.type) {
		case GameObject::GHOST:
			assetName = "Ghost"; break;
		case GameObject::STATIC:
			assetName = "Static"; break;
		case GameObject::DYNAMIC:
			assetName = "Dynamic"; break;
		}
		if (ImGui::BeginCombo(("##PhysicsType" + debug.name).c_str(), assetName.c_str())) {
			if (ImGui::Selectable("Ghost", physics.type == GameObject::GHOST)) {
				physics.type = GameObject::GHOST;
			}
			if (ImGui::Selectable("Static", physics.type == GameObject::STATIC)) {
				physics.type = GameObject::STATIC;
			}
			if (ImGui::Selectable("Dynamic", physics.type == GameObject::DYNAMIC)) {
				physics.type = GameObject::DYNAMIC;
			}
			ImGui::EndCombo();
		}

		ui::Separator();

		ui::Prop("Shape Scale", &physics.shapeScale);
		ui::Prop("Fixed Rotation", &physics.fixedRotation);
		ui::Prop("Is Bullet", &physics.isBullet);

		ui::Separator();

		ui::PropMask("Category", &physics.category);
		ui::PropMask("Mask", &physics.mask);
	}

	if (ImGui::IsAnyItemActive() && ImGui::IsWindowFocused()) {
		ReloadPhysics();
	}
}

std::vector<GameObject*> GameObject::GetChildren(bool recursive) {
	std::vector<GameObject*> out = m_children;

	if (recursive) {
		for (auto child : m_children) {
			auto rec = child->GetChildren(true);
			out.insert(out.end(), rec.begin(), rec.end());
		}
	}
	return out;
}

void GameObject::Initialize(Scene* scene) {
	m_scene = scene;

	assert (!m_initialized);
	m_initialized = true;

	InitializePhysics();

	for (auto child : m_children) {
		child->Initialize(scene);
	}
}

void GameObject::Update() {
	assert(m_initialized);

	for (auto child : m_children)
	{
		child->Update();
	}
}

void GameObject::Draw(Shader* shader, Mesh* mesh) {
	shader->Set("transform", GetWorldMatrix()); 
	shader->Set("sprite.color", sprite.color);

	auto tex = sprite.texture.Get();
	shader->Set("sprite.texture", 0);
	shader->Set("sprite.useTexture", (tex != nullptr));
	if (tex) { tex->Use(0); }

	mesh->Draw();

	for (auto child : m_children)
	{
		child->Draw(shader, mesh);
	}
}

void GameObject::ReloadPhysics() {
	// Remove the physicsBody
	if (m_scene) {
		if (m_physicsBody) {
			auto world = m_scene->GetBox2DWorld();
			world->DestroyBody(m_physicsBody);
		}
		// Adding it again
		InitializePhysics();
	}
}

void GameObject::InitializePhysics() {
	assert(m_scene);

	auto world = m_scene->GetBox2DWorld();

	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.angle = glm::radians(rotation);
	bodyDef.type = physics.type == PhysicsType::DYNAMIC ? b2_dynamicBody : b2_staticBody;
	bodyDef.fixedRotation = physics.fixedRotation;
	bodyDef.bullet = physics.isBullet;
	m_physicsBody = world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(
		scale.x * physics.shapeScale.x,
		scale.y * physics.shapeScale.y
	);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.filter.categoryBits = physics.category;
	fixture.filter.maskBits = physics.mask;
	switch (physics.type) {
	case PhysicsType::GHOST:
		fixture.filter.categoryBits = 0x000;
		break;
	case PhysicsType::STATIC:
		fixture.density = 0.f;
		break;
	case PhysicsType::DYNAMIC:
		fixture.density = 1.f;
		break;
	}
	m_physicsBody->CreateFixture(&fixture);

}

glm::mat4 GameObject::GetWorldMatrix() {
	if (m_parent) {
		return m_parent->GetWorldMatrix() * GetMatrix();
	}
	return GetMatrix();
}

void GameObject::RemoveParent() {
	auto parent = m_parent;

	if (m_parent)
	{
		auto it = std::find(m_parent->m_children.begin(), m_parent->m_children.end(), this);
		assert(it != m_parent->m_children.end()); // Make sure we found the child
		m_parent->m_children.erase(it);

		m_parent = nullptr;
	}
	if (parent) {
		SetLayer(parent->GetLayer());
	}
}

void GameObject::SetParent(GameObject* parent) {
	if (m_parent != nullptr)
	{
		RemoveParent();
	}
	m_parent = parent;
	parent->m_children.push_back(this);

	// Reset child position
	position = { 0.f, 0.f, };

	// Only root GameObjects can have a layer
	if (m_layer) {
		m_layer->Remove(this);
	}
	m_layer = nullptr;
}

GameObject* GameObject::GetParent() const {
	return m_parent;
}

GameObject* GameObject::GetRoot() {
	if (m_parent == nullptr) {
		return this;
	}

	return m_parent->GetRoot();
}

void GameObject::SetLayer(Layer* layer) {
	if (m_layer == layer || layer == nullptr) {
		return;
	}
	if (m_layer) {
		m_layer->Remove(this);
	}
	m_layer = layer;
	m_layer->objects.push_back(this);

	//We can't have a child object in a different layer then its parent
	if (m_parent) {
		RemoveParent();
	}
}

Layer* GameObject::GetLayer() {
	return GetRoot()->m_layer;
}

bool GameObject::IsInitialized() const {
	return m_initialized;
}

void GameObject::SubmitTransformToPhysicsWorld() {
	Transform transf;
	transf.SetMatrix(GetWorldMatrix());

	m_physicsBody->SetTransform(
		{ transf.position.x, transf.position.y }, 
		glm::radians(transf.rotation)
	);

	for (auto child : m_children) {
		child->SubmitTransformToPhysicsWorld();
	}
}

void GameObject::RetrieveTransformFromPhysicsWorld() {
	Transform transf;

	auto pos = m_physicsBody->GetPosition();
	auto rot = glm::degrees(m_physicsBody->GetAngle());

	transf.position = { pos.x, pos.y };
	transf.rotation = rot;

	//Scaling does not change
	transf.scale = scale;

	if (m_parent) {
		SetMatrix(glm::inverse(m_parent->GetWorldMatrix()) * transf.GetMatrix());
	}
	else {
		SetMatrix(transf.GetMatrix());
	}
}

void GameObject::Kill() {
	m_killed = true;
}
