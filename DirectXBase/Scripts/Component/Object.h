#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "Component.h"
#include <list>

class Component;

class Object final
{
public:
	Object();
	virtual ~Object();

	void Awake();
	void OnEnable();
	void Start();
	void Update();
	void FixedUpdate();
	void OnDisEnable();
	void Terminate();

	template <typename T>
	T* AddComponent()
	{
		//assert(std::is_base_of<Component, T>::value == false, "Component is base of D");
		T* buff = new T();
		buff->SetParent(this);
		m_listComponent.push_back(buff);
		return buff;
	}

private:
	std::list<Component*> m_listComponent;
	// --- transform�ɂ܂Ƃ߂�Object�ɃR���|�W�V�����Ŏ�������B---
	Object* m_parent;
	std::list<Object*> m_listChild;
	// -------------------------------------------------------
};

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

public:
	static std::list<Object*> m_listObject;

	void Update();
};

#endif // !__OBJECT_H__
