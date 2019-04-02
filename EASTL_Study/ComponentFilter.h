#pragma once
#include "EntityTypes.h"
#include "TypeID.h"

template<typename... Args>
struct TypeList {};

template<typename... Args>
struct Requires : TypeList<Args...> {};

template<typename... Args>
struct Excludes : TypeList<Args...> {};

template<typename... Args>
static void Types(EntityComponentArray&, TypeList<Args...>) {};

template<typename Type, typename... Args>
static void Types(EntityComponentArray& components, TypeList<Type, Args...>)
{
	components[TypeID<Component>::GetId<Type>()] = 1;
	Types(components, TypeList<Args...>());
};

struct ComponentFilter
{

private:
	EntityComponentArray m_requires;
	EntityComponentArray m_excludes;
public:
	ComponentFilter()
	{
		for (int i = 0; i < MAX_COMPONENTS; ++i)
		{
			m_requires[i] = 0;
			m_excludes[i] = 0;
		}
	}

	ComponentFilter(const EntityComponentArray& requireComponents, const EntityComponentArray& excludedComponents)
		: m_requires(requireComponents)
		, m_excludes(excludedComponents)
	{
	}
	~ComponentFilter()
	{

	}

	bool operator==(const ComponentFilter& other)
	{
		return ((*this).m_requires == other.m_requires);
	}

	bool Compare(const EntityComponentArray& components)
	{
		for (int i = 0; i < MAX_COMPONENTS; ++i)
		{
			if (m_requires[i] == 1 && components[i] == -1)
				return false;

			if (m_excludes[i] == 1 && components[i] != -1)
				return false;
		}

		return true;
	}

};

template<typename RequireList, typename ExcludeList = Excludes<>>
ComponentFilter CreateFilter()
{
	EntityComponentArray requires;
	EntityComponentArray excludes;

	for (int i = 0; i < MAX_COMPONENTS; ++i)
	{
		requires[i] = 0;
		excludes[i] = 0;
	}

	Types(requires, RequireList());
	Types(excludes, ExcludeList());

	return ComponentFilter(requires, excludes);
}