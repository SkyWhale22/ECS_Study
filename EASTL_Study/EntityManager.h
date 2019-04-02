#pragma once

#include "ComponentManager.h"
#include "TypeID.h"
#include "EntityTypes.h"
#include <atomic>
#include "Component.h"

class System;

using Entities = std::vector<Entity>;

// TODO
// : Make variations of AddComponent
// : Allow to add components when creating an entity
// : Make RemoveComponent()
class EntityManager
{
private:
	Entity m_nextEntity {0};
	ComponentManager* m_pComponent = nullptr;
	std::vector<System*> m_systems;
	
public:
	EntityManager();

	~EntityManager();
	 
	void Update(float deltaTime);
	void Deallocate();

	const Entities& GetEntities(ComponentFilter filter);;

	Entity CreateEntity();

	template<typename Type>
	void AddComponent(Entity entId);

	template<typename Type>
	Type& GetComponent(Entity entId);

	
	template<typename Type>
	void AddSystem();

};

template<typename Type>
inline void EntityManager::AddComponent(Entity entId)
{
	Type* pComponent = new Type();
	int id = TypeID<Component>::GetId<Type>();
	m_pComponent->AddComponent(entId - 1, pComponent, TypeID<Component>::GetId<Type>());
}

template<typename Type>
inline Type & EntityManager::GetComponent(Entity entId)
{
	return static_cast<Type&>(m_pComponent->GetComponent(entId - 1, TypeID<Component>::GetId<Type>()));
}

template<typename Type>
inline void EntityManager::AddSystem()
{
	m_systems.push_back(new Type(*this));
}
