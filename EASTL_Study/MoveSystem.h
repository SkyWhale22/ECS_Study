#pragma once
#include "System.h"

class MoveSystem : public System
{
public:
	MoveSystem(EntityManager& manager);
	~MoveSystem();

	virtual void Update(float deltaTime) override;
};
