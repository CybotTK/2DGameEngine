#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

class Transform{
public:
	Transform();
	virtual ~Transform();
	
	glm::mat4 GetMatrix();

	glm::vec2 position;
	glm::vec2 scale = {1.f, 1.f};
	float rotation  = 0.f; //in degrees
};

#endif // !TRANSFORM_H
