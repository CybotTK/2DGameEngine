#include "Core/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewProjection(float aspect) const
{
	auto proj = glm::ortho(-area * aspect, area * aspect, -area, area, -100.f, 100.f);
	return proj * glm::inverse(GetMatrix());
}
