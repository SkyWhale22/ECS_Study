#pragma once

struct Component
{

};

struct Vec2D
{
	float m_x;
	float m_y;
};

struct TransformComponent : public Component
{
	Vec2D m_position;
};

struct Renderable : public Component
{
	bool m_render;
	const char* m_pHash;
};

struct HealthComponent : public Component
{
	int m_hp;
	int m_maxHp;
	bool m_isDead;
};
