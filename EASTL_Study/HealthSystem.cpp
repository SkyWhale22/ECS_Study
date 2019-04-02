#include "HealthSystem.h"
#include "Component.h"
#include <iostream>

HealthSystem::HealthSystem(EntityManager & manager)
	: System(manager, CreateFilter<Requires<HealthComponent>>())
{
}

HealthSystem::~HealthSystem()
{
}

void HealthSystem::Update(float deltaTime)
{
	const auto& entities = GetEntities();

	for (Entity entId : entities)
	{
		auto& health = GetComponent<HealthComponent>(entId);

		if (!health.m_isDead)
		{
			std::cout << "<HealthSystem> entity " << entId << " 's health: " << health.m_hp << " / " << health.m_maxHp << std::endl;
			--health.m_hp;
			
			if (health.m_hp <= 0)
			{
				health.m_isDead = true;
			}
		}
		else
		{
			std::cout << "<HealthSystem> entity " << entId << " is dead!" << std::endl;
		}

	}
}

