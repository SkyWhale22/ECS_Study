#include "System.h"
#include "Component.h"
#include <iostream>
#include <string>

System::System(EntityManager & manager)
	: m_manager(manager)
{
}

System::~System() = default;

System::System(EntityManager & manager, const ComponentFilter & filter)
	: m_manager(manager)
	, m_filter(filter)
{
}

const std::vector<Entity>& System::GetEntities()
{
	return m_manager.GetEntities(m_filter);
}
//
//
