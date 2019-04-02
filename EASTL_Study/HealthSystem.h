#pragma once
#include "System.h"
class HealthSystem : public System
{
public:
	HealthSystem(EntityManager& manager);
	~HealthSystem();

	virtual void Update(float deltaTime) override;
};
