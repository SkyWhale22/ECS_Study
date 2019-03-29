#include "Test.h"

#include <new>
#define EA_COMPILER_IS_CPLUSPLUS_0X // Visual C++ 2010対策
#include <EASTL/vector.h>
#include <EASTL/bitset.h>
#include <memory>
using namespace TEST;


void* operator new[](size_t size, const char* pName, int flags,
	unsigned debugFlags, const char* file, int line)
{
	return operator new[](size);
}
void* operator new[](size_t size, size_t alignment, size_t alignmentOffset,
	const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	// doesn't support alignment
	return operator new[](size);
}

void operator delete[](void* ptr, const char* pName, int flags,
	unsigned debugFlags, const char* file, int line)
{
	operator delete[](ptr);
}
void operator delete[](void* ptr, size_t alignment, size_t alignmentOffset,
	const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	// doesn't support alignment
	operator delete[](ptr);
}

template<typename Type>
struct VecOfVec: public eastl::vector<eastl::vector<Type>> {};

class Component
{
protected:
	int ownerId;

public:
	virtual ~Component() = 0;
	virtual void Print() { cout << "ownerId: " << ownerId; }
};

class Transform : public Component
{
public:
	Transform() {}
	Transform(int id) { ownerId = id; }

	virtual void Print() override { Component::Print(); cout << "Transform" << endl; }
};

class Speed : public Component
{
public:
	Speed(int id) { ownerId = id; }

	virtual void Print() override { Component::Print(); cout << "Speed" << endl; }
};

class Health : public Component
{
public:
	Health(int id) { ownerId = id; }

	virtual void Print() override { Component::Print(); cout << "Health" << endl; }
};

class Sound : public Component
{
public:
	Sound(int id) { ownerId = id; }

	virtual void Print() override { Component::Print(); cout << "Sound" << endl; }
};

using ComponentId = size_t;

ComponentId GetComponentId()
{
	// last ID
	static ComponentId lastID = 0;
	return ++lastID;
}

template <typename Type>
ComponentId GetComponentId()
{
	static ComponentId typeID = GetComponentId();
	return typeID;
}

class EntityManager
{
public:
	using ComponentBitSet= eastl::bitset<32>; // 
	using EntityBitSet = eastl::bitset<32>; // 

	eastl::vector<Entity*> entities;
	eastl::vector<eastl::vector<std::unique_ptr<Component>>*> components;


	ComponentBitSet componentBitSet;
	EntityBitSet entityBitSet;
public:
	EntityManager()
	{

	}
	~EntityManager()
	{
		components.clear();
	}

	void CreateEntity()
	{
		entities.push_back(new Entity());
	}

	template<typename Type>
	bool HasComponent() const
	{
		return componentBitSet[GetComponentID<Type>()];
	}

	template<class CompType>
	void AddComponent(int id)
	{

		// If given component was never created.
		//if (!HasComponent<CompType>())
		//{
		//	components.emplace_back(new eastl::vector< std::unique_ptr<Component>>());
		//}
		//	   		 	  
		//CompType* pComponent(new CompType(id));
		//std::unique_ptr<Component> ptr{ pComponent };
		//eastl::vector<std::unique_ptr<Component>>& temp = *components[GetComponentId<CompType>() - 1];
		//temp.emplace_back(ptr);
		//components[GetComponentId<CompType>() - 1]->push_back(ptr);

		////m_componentArray[GetComponentID<Type>()] = pComponent;
		//componentBitSet[GetComponentID<CompType>()] = true;


/*
		Type* pComponent(new Type(std::forward<TArgs>(args)...));
		pComponent->m_pEntity = this;
		std::unique_ptr<Component> ptr{ pComponent };
		m_components.emplace_back(std::move(ptr));

		m_componentArray[GetComponentID<Type>()] = pComponent;
		m_componentBitSet[GetComponentID<Type>()] = true;

		pComponent->Init();

		return *pComponent;
*/
	}

	template<class Type>
	void Test()
	{
		eastl::vector<Type>* testVec = new eastl::vector<Type>();
		if (testVec)
			cout << "Success" << endl;
		delete testVec;
	}

	void RunTest()
	{
		for (unsigned int i = 0; i < components.size(); ++i)
		{

			//for(TestClass* pClass : *pTest)
			//	pClass->Print();
			for (unsigned int j = 0; j < components[i]->size(); ++j)
				components.at(i)->at(j)->Print();
		}
	}
};

int main()
{
	EntityManager manager;

	manager.CreateEntity();
	//manager.CreateEntity();
	//manager.CreateEntity();


	manager.AddComponent<Transform>(0);
	//manager.AddComponent<Health>(0);
	//manager.AddComponent<Speed>(0);
	//manager.AddComponent<Sound>(0);

	//manager.AddComponent<Health>(1);
	//manager.AddComponent<Speed>(1);
	//manager.AddComponent<Sound>(1);

	//manager.AddComponent<Speed>(2);
	//manager.AddComponent<Speed>(2);

	//manager.RunTest();

	/*test.push_back(new eastl::vector<TestClass*>());
	test.push_back(new eastl::vector<TestClass*>());
	test.push_back(new eastl::vector<TestClass*>());
	test.push_back(new eastl::vector<TestClass*>());
	test.push_back(new eastl::vector<TestClass*>());

	test[0]->push_back(new TestClass());
	test[0]->push_back(new TestClass());
	test[0]->push_back(new TestClass());
	test[0]->push_back(new TestClass());
	test[0]->push_back(new TestClass());

	test[1]->push_back(new TestClass());
	test[1]->push_back(new TestClass());
	test[1]->push_back(new TestClass());
	test[1]->push_back(new TestClass());
	test[1]->push_back(new TestClass());

	test[2]->push_back(new TestClass());
	test[2]->push_back(new TestClass());
	test[2]->push_back(new TestClass());
	test[2]->push_back(new TestClass());
	test[2]->push_back(new TestClass());

	test[3]->push_back(new TestClass());
	test[3]->push_back(new TestClass());
	test[3]->push_back(new TestClass());
	test[3]->push_back(new TestClass());
	test[3]->push_back(new TestClass());

	test[0]->erase(test[0]->begin() + 2);
	test[0]->erase(test[0]->begin() + 1);


	test[4]->push_back(new TestClass());
	test[4]->push_back(new TestClass());
	test[4]->push_back(new TestClass());
	test[4]->push_back(new TestClass());
	test[4]->push_back(new TestClass());

	test[2]->erase(test[2]->begin() + 2);
	test[2]->erase(test[2]->begin() + 1);
	test[2]->erase(test[2]->begin() + 1);*/


	//for (eastl::vector<TestClass*>* pTest : test)
	//for(unsigned int i = 0; i < test.size(); ++i)
	//{

	//	//for(TestClass* pClass : *pTest)
	//	//	pClass->Print();
	//	for (unsigned int j = 0; j < test[i]->size(); ++j)
	//		test.at(i)->at(j)->Print(i, j);
	//}

	system("pause");

	return 0;
}