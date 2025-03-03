#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include "Core/Layer.h"
#include "Core/Camera.h"
#include "Core/GameObject.h"

#include "Asset/Object.h"

class Mesh; // Reduces compilation time cause it doesn't need to compile everything from the mesh
			// Also changes made to Mesh.h won't force recompilation of any file that has Scene.h
class Shader;

class Scene : public Object{
public:
	Scene();
	virtual ~Scene();

	virtual void Save(File* file) override;
	virtual void Load(File* file) override;

	virtual void DrawUI() override;

	void Update();
	void UpdatePhysics(float deltaTime);
	void Draw(Shader* shader, float aspect);

	// We call this at the end of every frame. 
	// Use it to cleanup stuff
	void EndUpdate();

	b2World* GetBox2DWorld() const;

	// It returns all the objects from all layers 
	std::vector<GameObject*> GetObjectsRecursively();

	glm::vec2 GetGravity();
	void SetGravity(glm::vec2 value);
	void SetGravity(float x, float y);

	Camera camera;
	std::vector<Layer*> layers;

	glm::vec3 background = { 0.1f, 0.5f, 0.8f };
protected:
	b2World* m_physicsWorld = nullptr;
};

#endif // !SCENE_H
