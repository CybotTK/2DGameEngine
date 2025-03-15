#include "Core/Component.h"
#include <iostream>

Component::Component(GameObject* owner) : m_owner(owner) {
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
