#include "ComponentManager.h"
#include "ComponentFilter.h"
#include "Component.h"

ComponentManager::ComponentManager()
{
	m_components.reserve(MAX_COMPONENTS);
	m_entityComponents.reserve(MAX_ENTITIES);
	m_entityComponents.reserve(MAX_ENTITIES);

	for (size_t i = 0; i < MAX_COMPONENTS; ++i)
	{
		m_components.push_back(ComponentArray());
		m_components[i].reserve(MAX_ENTITIES);
	}
}


ComponentManager::~ComponentManager()
{
	for (ComponentArray& arr : m_components)
	{
		for (Component* pComp : arr)
		{
			delete pComp;
			pComp = nullptr;
		}
	}
}

void ComponentManager::Deallocate()
{
}

void ComponentManager::AddEntity()
{
	m_entityComponents.push_back(EntityComponentArray());
	EntityComponentArray& components = m_entityComponents[m_entityComponents.size() - 1];
	for (unsigned int i = 0; i < MAX_COMPONENTS; ++i)
	{
		components[i] = -1;
	}
}

void ComponentManager::AddComponent(Entity entId, Component* pComponent, ComponentId compId)
{
	m_components[compId].push_back(pComponent);
	m_entityComponents[entId][compId] = m_components[compId].size() - 1;
}

Component& ComponentManager::GetComponent(Entity entId, ComponentId compId)
{
	const int index = m_entityComponents[entId][compId];
	return *m_components[compId][index];
}

bool ComponentManager::HasComponent(Entity entId, ComponentId compId)
{
	if (m_entityComponents.size() <= 0)
		return false;
	return m_entityComponents[entId][compId] != -1;
}

const std::vector<Entity>& ComponentManager::GetEntities(ComponentFilter filter)
{
	m_entitiesToReturn.clear();

	for (size_t i = 0; i < m_entityComponents.size(); ++i)
	{
		if (filter.Compare(m_entityComponents[i]) == true)
		{
			m_entitiesToReturn.push_back(i);
		}
	}

	return m_entitiesToReturn;
}
