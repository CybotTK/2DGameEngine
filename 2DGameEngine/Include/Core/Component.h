#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component {
public:
	Component(GameObject* owner);
	virtual ~Component();

	virtual void Start();
	virtual void Update();
	virtual void End();

	GameObject* GetOwner() const;
protected:
	GameObject* m_owner = nullptr;
};

#endif // !COMPONENT_H
