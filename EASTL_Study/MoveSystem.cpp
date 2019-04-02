#include "MoveSystem.h"
#include "Component.h"
#include <iostream>

MoveSystem::MoveSystem(EntityManager & manager)
	: System(manager, CreateFilter<Requires<TransformComponent, HealthComponent>>())
{
}

MoveSystem::~MoveSystem()
{
}

void MoveSystem::Update(float deltaTime)
{
	const auto& entities = GetEntities();

	for (Entity entId : entities)
	{
		auto& transform = GetComponent<TransformComponent>(entId);
		auto& health = GetComponent<HealthComponent>(entId);

		if (!health.m_isDead)
		{
			std::cout << "<MoveSystem> entity " << entId << " is located at x: " << transform.m_position.m_x << ", y: " << transform.m_position.m_y << std::endl;
			++transform.m_position.m_x;
			++transform.m_position.m_y;
		}
	}
}
