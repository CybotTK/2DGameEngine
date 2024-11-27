#include "Core/Transform.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp> //transform.hpp if stuff starts to not work
#include <glm/gtx/quaternion.hpp> //transform.hpp if stuff starts to not work
#include <glm/gtx/matrix_decompose.hpp> //transform.hpp if stuff starts to not work

Transform::Transform()
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::GetMatrix() const
{
	glm::mat4 pos = glm::translate(glm::vec3(position, 0.f));
	glm::mat4 rot = glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
	glm::mat4 scl = glm::scale(glm::vec3(scale, 1.f));

	return pos * rot * scl;
}

void Transform::SetMatrix(glm::mat4 matrix)
{
	glm::vec3 skew, scl, pos;
	glm::vec4 perspective;
	glm::quat quaternion;

	glm::decompose(matrix, scl, quaternion, pos, skew, perspective);

	position = pos;
	rotation = glm::eulerAngles(glm::normalize(quaternion)).z * (180.f / glm::pi<float>());
	scale = scl;
}
