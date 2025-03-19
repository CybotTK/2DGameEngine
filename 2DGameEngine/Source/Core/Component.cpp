#include "Core/Component.h"
#include "Core/GameObject.h"
#include <iostream>

Component::Component(GameObject* owner) : m_owner(owner) {
	std::cout << "Set Owner: " << m_owner->debug.name << std::endl;
	std::cout << "Rotation of Owner: " << m_owner->rotation << std::endl;
}

Component::~Component() {
}

void Component::Start() {
	
}

void Component::Update() {
	
}

void Component::End() {

}

GameObject* Component::GetOwner() const {
	return m_owner;
}
