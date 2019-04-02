#pragma once

#include "ComponentFilter.h"
#include "EntityManager.h"

class System
{
protected:
	ComponentFilter m_filter;
	EntityManager& m_manager;
	
public:
	System(EntityManager& manager);
	System(EntityManager& manager, const ComponentFilter& filter);
	virtual ~System() = 0;

	virtual void Update(float deltaTime) = 0;
	const std::vector<Entity>& GetEntities();

	template<typename Type>
	Type& GetComponent(Entity entity);

	void operator=(System*) = delete;
};

template<typename Type>
inline Type & System::GetComponent(Entity entity)
{
	return m_manager.GetComponent<Type>(entity + 1);
}
