#include "EntityManager.h"

#include "RenderSystem.h"
#include "HealthSystem.h"
#include "MoveSystem.h" 

#include <iostream>
#include <vld.h>

int main()
{
	EntityManager manager;

	// -- First entity ---
	Entity first = manager.CreateEntity();
	manager.AddComponent<TransformComponent>(first);
	manager.AddComponent<Renderable>(first);
	manager.AddComponent<HealthComponent>(first);

	auto& firatTrans = manager.GetComponent<TransformComponent>(first);
	firatTrans.m_position.m_x = 10;
	firatTrans.m_position.m_y = 20;

	auto& firstRender = manager.GetComponent<Renderable>(first);
	firstRender.m_pHash = "First";
	firstRender.m_render = true;

	auto& firstHealth = manager.GetComponent<HealthComponent>(first);
	firstHealth.m_hp = firstHealth.m_maxHp = 700;
	firstHealth.m_isDead = false;

	// -- Second entity ---
	Entity second = manager.CreateEntity();
	manager.AddComponent<TransformComponent>(second);
	manager.AddComponent<Renderable>(second);

	auto& secondTrans = manager.GetComponent<TransformComponent>(second);
	secondTrans.m_position.m_x = 30;
	secondTrans.m_position.m_y = 40;

	auto& secondRender = manager.GetComponent<Renderable>(second);
	secondRender.m_pHash = "Second";
	secondRender.m_render = true;


	// -- Third entity ---
	Entity third = manager.CreateEntity();
	manager.AddComponent<TransformComponent>(third);
	manager.AddComponent<HealthComponent>(third);
	manager.AddComponent<Renderable>(third);

	auto& thirdTrans = manager.GetComponent<TransformComponent>(third);
	thirdTrans.m_position.m_x = 100;
	thirdTrans.m_position.m_y = 100;

	auto& thirdHealth = manager.GetComponent<HealthComponent>(third);
	thirdHealth.m_hp = thirdHealth.m_maxHp = 10;
	thirdHealth.m_isDead = false;

	auto& thirdRender = manager.GetComponent<Renderable>(third);
	thirdRender.m_pHash = "Third";
	thirdRender.m_render = true;


	// -- Fourth entity ---
	Entity fourth = manager.CreateEntity();
	manager.AddComponent<TransformComponent>(fourth);
	manager.AddComponent<Renderable>(fourth);
	manager.AddComponent<HealthComponent>(fourth);

	auto& fourthTrans = manager.GetComponent<TransformComponent>(fourth);
	fourthTrans.m_position.m_x = 200;
	fourthTrans.m_position.m_y = 200;

	auto& render2 = manager.GetComponent<Renderable>(fourth);
	render2.m_pHash = "Fourth";
	render2.m_render = true;

	auto& fourthHealth = manager.GetComponent<HealthComponent>(fourth);
	fourthHealth.m_hp = fourthHealth.m_maxHp = 100;
	fourthHealth.m_isDead = false;


	manager.AddSystem<RenderSystem>();
	manager.AddSystem<MoveSystem>();
	manager.AddSystem<HealthSystem>();


	for (size_t i = 0; i < 500; ++i)
	{
		manager.Update(0.f);

		system("cls");
	}

	manager.Deallocate();

	system("pause");

	return 0;
}