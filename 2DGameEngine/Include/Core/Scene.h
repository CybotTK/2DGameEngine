#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include "Core/Layer.h"
#include "Core/Camera.h"
#include "Core/GameObject.h"

class Mesh; // Reduces compilation time cause it doesn't need to compile everything from the mesh
			// Also changes made to Mesh.h won't force recompilation of any file that has Scene.h
class Shader;

class Scene {
public:
	Scene();
	virtual ~Scene();

	void Update();
	void Draw(Shader* shader, float aspect);

	Camera camera;
	std::vector<Layer*> layers;

	glm::vec3 background = { 0.1f, 0.5f, 0.8f };
};

#endif // !SCENE_H
