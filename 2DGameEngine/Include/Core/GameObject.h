#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <Box2D/Box2D.h>

#include "Asset/Asset.h"
#include "Asset/Object.h"

#include "Core/Transform.h"

#include "Graphics/Textures/ImageTexture.h"

class Layer;
class Shader;
class Mesh;
class Scene;

typedef uint16 CollisionMask;

class GameObject : public Object, public Transform {
	friend class App;
	friend class Scene;
public:
	GameObject();
	virtual ~GameObject();

	virtual void Save(File* file) override;
	virtual void Load(File* file) override;

	virtual void DrawUI() override;

	std::vector<GameObject*> GetChildren(bool recursive = true);

	virtual void Initialize(Scene* scene);
	void Update();
	void Draw(Shader* shader, Mesh* mesh);

	void ReloadPhysics();

protected:
	void InitializePhysics();
public:

	glm::mat4 GetWorldMatrix();

	void RemoveParent();
	void SetParent(GameObject* parent);
	GameObject* GetParent() const;

	// Returns itself if GameObject has no parent. The root parent, otherwise 
	GameObject* GetRoot();

	// Note: Only root GameObjects (with no parents) can have layers
	void SetLayer(Layer* layer);
	Layer* GetLayer();

	bool IsInitialized() const;

	void SubmitTransformToPhysicsWorld();
	void RetrieveTransformFromPhysicsWorld();

	//Destroys the object and its children
	void Kill();

	struct _Sprite {
		glm::vec4 color = {1.f, 1.f, 1.f, 1.f};
		AssetHandler<ImageTexture> texture;
		AssetHandler<Mesh>		   shape;
	} sprite;

	enum PhysicsType {
		GHOST,
		STATIC,
		DYNAMIC
	};

	struct _Physics {
		PhysicsType type = PhysicsType::STATIC;

		CollisionMask category  = 0x0001;
		CollisionMask mask		= 0xFFFF;

		glm::vec2 shapeScale = { 1.f, 1.f }; //Relative to the object's scale
	
		bool fixedRotation = false;
		bool isBullet = false;
	} physics;

	// Optimization. 
	// The engine will not run any game logic if this is false
	// it also includes the construction script
	bool runLogic = false; // LATER USE

	std::string constructionScript;

	// True means the user deleted the object 
	// False means the user closed the app
	bool deletedInEditor = false;
private:
	Scene* m_scene = nullptr;	
	Layer* m_layer = nullptr;

	b2Body* m_physicsBody = nullptr;

	GameObject* m_parent;
	std::vector<GameObject*> m_children;

	bool m_initialized = false;
	bool m_killed = false;  // True means it will be garbage collected 
							// in the end frame

};

#endif // !GAME_OBJECT_H
