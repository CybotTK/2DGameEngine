#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include "Core/GameObject.h"
#include "Core/Camera.h"

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

	std::vector<GameObject*> objects;
protected:
	Mesh* m_plane; // I declare pointer cause I don't need full definition of Mesh
};

#endif // !SCENE_H
