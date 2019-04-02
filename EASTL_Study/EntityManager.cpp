#include "EntityManager.h"
#include "System.h"

EntityManager::EntityManager()
	: m_nextEntity(0)
{
	m_pComponent = new ComponentManager();
};

EntityManager::~EntityManager()
{
	delete m_pComponent;
	m_pComponent = nullptr;

	for (auto& system : m_systems)
	{
		delete system;
		system = nullptr;
	}

	m_systems.clear();
};

void EntityManager::Update(float deltaTime)
{
	for (System* system : m_systems)
	{
		system->Update(deltaTime);
	}
}

void EntityManager::Deallocate()
{
	delete m_pComponent;
	m_pComponent = nullptr;
}

const Entities& EntityManager::GetEntities(ComponentFilter filter)
{
	return m_pComponent->GetEntities(filter);
}

Entity EntityManager::CreateEntity()
{
	Entity entity = ++m_nextEntity;
	m_pComponent->AddEntity();
	return entity;
}
