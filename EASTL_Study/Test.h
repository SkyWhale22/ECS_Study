#pragma once

#include <EASTL/vector.h>
#include <EASTL/bitset.h>
#include <iostream>

using std::cout;
using std::endl;

class Component;

using EntityId = size_t;
using EntityTypeId = size_t;

inline EntityTypeId GetEntityTypeId()
{
	// last ID
	static EntityTypeId lastID = 0;
	return ++lastID;
}

inline EntityId GetEntityId()
{
	// last ID
	static EntityId lastID = 0;
	return ++lastID;
}

using ComponentID = size_t;

inline ComponentID GetComponentID()
{
	// last ID
	static ComponentID lastID = 0;
	return ++lastID;
}

template <typename Type>
inline ComponentID GetComponentID()
{
	static ComponentID typeID = GetComponentID();
	return typeID;
}

namespace TEST
{
	class Entity
	{
		using ComponentBitSet = eastl::bitset<32>; // Total : 32

	private:
		int m_id;
		eastl::vector<Component*> components;
		ComponentBitSet compBitSet;

	public:
		Entity()
		{
			m_id = GetEntityId();
		}

		template <typename Type>
		bool HasComponent() const
		{
			return compBitSet[GetComponentID<Type>()];
		}

		template <typename Type>
		void AddComponent(Component* comp)
		{
			if(!HasComponent<Type>())
				components.emplace_back(comp);
		}

		void Print(int index1, int index2)
		{
			cout << "index1: " << index1 << " index2: " << index2 << " id: " << m_id << endl;
		}
	};
}
