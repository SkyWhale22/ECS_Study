#pragma once

#include "EntityTypes.h"

struct ComponentFilter;
struct Component;


class ComponentManager
{
private:
	std::vector<EntityComponentArray>	m_entityComponents;
	std::vector<Entity>					m_entitiesToReturn;
	std::vector<ComponentArray>			m_components;

public:
	ComponentManager();
	~ComponentManager();

	void Deallocate();
	void AddEntity();
	void AddComponent(Entity entId, Component* pComponent, ComponentId compId);

	Component& GetComponent(Entity entId, ComponentId compId);
	bool HasComponent(Entity entId, ComponentId compId);
	const std::vector<Entity>& GetEntities(ComponentFilter filter);
};
