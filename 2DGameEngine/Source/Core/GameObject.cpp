#include "Core/GameObject.h"

#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"

GameObject::GameObject()
{
	sprite.shape.Set("Plane");
}

GameObject::~GameObject()
{
	for (auto child : m_children)
	{
		delete child;
	}
	m_children.clear();
}

void GameObject::Update()
{
	rotation += 0.1f;

	for (auto child : m_children)
	{
		child->Update();
	}
}

void GameObject::Draw(Shader* shader, Mesh* mesh)
{
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

glm::mat4 GameObject::GetWorldMatrix()
{
	if (m_parent)
	{
		return m_parent->GetWorldMatrix() * GetMatrix();
	}
	return GetMatrix();
}

void GameObject::RemoveParent()
{
	if (m_parent)
	{
		auto it = std::find(m_parent->m_children.begin(), m_parent->m_children.end(), this);
		assert(it != m_parent->m_children.end()); // Make suer we found the child
		m_parent->m_children.erase(it);

		m_parent = nullptr;
	}
}

void GameObject::SetParent(GameObject* parent)
{
	if (m_parent != nullptr)
	{
		RemoveParent();
	}
	m_parent = parent;
	parent->m_children.push_back(this);

	// Reset child position
	position = { 0.f, 0.f, };
}

GameObject* GameObject::GetParent() const
{
	return m_parent;
}
