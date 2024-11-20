#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Core/Asset.h"
#include "Core/Transform.h"
#include "Graphics/Textures/ImageTexture.h"

class Shader;
class Mesh;

class GameObject : public Transform {
public:
	GameObject();
	virtual ~GameObject();

	void Update();
	void Draw(Shader* shader, Mesh* mesh);

	glm::mat4 GetWorldMatrix();

	void RemoveParent();
	void SetParent(GameObject* parent);
	GameObject* GetParent() const;

	std::string name = "Game Object";

	struct _Sprite {
		glm::vec4 color = {1.f, 1.f, 1.f, 1.f};
		AssetHandler<ImageTexture> texture;
		AssetHandler<Mesh>		   shape;
	} sprite;

private:
	GameObject* m_parent;
	std::vector<GameObject*> m_children;

};

#endif // !GAME_OBJECT_H
