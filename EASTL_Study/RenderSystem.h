#pragma once
#include "System.h"

class RenderSystem : public System
{
public:
	RenderSystem(EntityManager& manager);
	~RenderSystem();

	virtual void Update(float deltaTime) override;
};
