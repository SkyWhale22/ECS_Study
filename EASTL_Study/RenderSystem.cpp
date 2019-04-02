#include "RenderSystem.h"
#include "Component.h"
#include <iostream>

RenderSystem::RenderSystem(EntityManager & manager)
	: System(manager, CreateFilter<Requires<TransformComponent, Renderable>>())
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Update(float deltaTime)
{
	const auto& entities = GetEntities();

	for(Entity entId : entities)
	{
		auto& render = GetComponent<Renderable>(entId);
		
		if (!render.m_render)
			continue;
		
		auto& transform = GetComponent<TransformComponent>(entId);


		std::cout << "<RenderSystem> Rendering entity " << entId << " at " << transform.m_position.m_x << ", " << transform.m_position.m_y << std::endl;
	}
}
