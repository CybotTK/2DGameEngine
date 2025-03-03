#include "Core/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Save(File* file) {
	Object::Save(file);

	// Transform save
	file->Write(position);
	file->Write(rotation);
	file->Write(scale);

	file->Write(area);
}

void Camera::Load(File* file) {
	Object::Load(file);

	// Transform save
	file->Read(position);
	file->Read(rotation);
	file->Read(scale);

	file->Read(area);
}

glm::mat4 Camera::GetViewProjection(float aspect) const
{
	auto proj = glm::ortho(-area * aspect, area * aspect, -area, area, -100.f, 100.f);
	return proj * glm::inverse(GetMatrix());
}
