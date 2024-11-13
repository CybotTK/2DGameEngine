#include "Core/Transform.h"

#include <glm/gtx/transform.hpp> //transform.hpp if stuff starts to not work

Transform::Transform()
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::GetMatrix()
{
	glm::mat4 pos = glm::translate(glm::vec3(position, 0.f));
	glm::mat4 rot = glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
	glm::mat4 scl = glm::scale(glm::vec3(scale, 1.f));

	return pos * rot * scl;
}
