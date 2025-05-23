#ifndef CAMERA_H
#define CAMERA_H

#include "Core/Transform.h"

#include "Asset/Object.h"

class Camera : public Object, public Transform {
public:
	Camera();
	virtual ~Camera();

	virtual void Save(File* file) override;
	virtual void Load(File* file) override;

	glm::mat4 GetViewProjection(float aspect = 1.f) const;

	float area = 5.f;
};

#endif // !CAMERA_H
