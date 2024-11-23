#ifndef CAMERA_H
#define CAMERA_H

#include "Core/Transform.h"

class Camera : public Transform {
public:
	Camera();
	virtual ~Camera();

	glm::mat4 GetViewProjection(float aspect = 1.f) const;

	float area = 5.f;
};

#endif // !CAMERA_H
