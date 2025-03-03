#ifndef LAYER_H
#define LAYER_H

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <Core/GameObject.h>
#include <Core/Camera.h>

#include "Asset/Object.h"

class Shader;
class Scene;

class Layer : public Object{
public:
	Layer(Scene* scene, const std::string& layerName = "Layer");
	virtual ~Layer();

	virtual void Save(File* file) override;
	virtual void Load(File* file) override;

	void Update();
	void Draw(const Camera& cam, Shader* shader, float aspect);

	// Creates a game object on the fly
	GameObject* NewObject();

	virtual void DrawUI() override;

	void Add(GameObject* object);
	void Remove(GameObject* object);

	// Returns the layer index in the scene's layer vector
	int GetLayerIndex();

	void MoveUp();
	void MoveDown();

	// It will remove all non root objects from the list
	void CleanupObjectList();

	// It returns all the objects (and children)
	std::vector<GameObject*> GetObjectsRecursively();

	glm::vec4 tint = { 1.f, 1.f, 1.f, 1.f };
	bool useCamera = true;

	std::vector<GameObject*> objects;
private:
	Scene* m_scene;
};

#endif // !LAYER_H
