#include "Entity.h"
#include "Component.h"
#include "System.h"

//#include <new>
//#define EA_COMPILER_IS_CPLUSPLUS_0X // Visual C++ 2010対策
#include <vector>
#include <bitset>
#include <memory>
#include <vld.h>
//
//void* operator new[](size_t size, const char* pName, int flags,
//	unsigned debugFlags, const char* file, int line)
//{
//	return operator new[](size);
//}
//void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, 
//	const char* pName, int flags, unsigned debugFlags, const char* file, int line)
//{
//	// doesn't support alignment
//	return operator new[](size);
//}
//
//void operator delete[](void* ptr, const char* pName, int flags,
//	unsigned debugFlags, const char* file, int line)
//{
//	operator delete[](ptr);
//}
//void operator delete[](void* ptr, size_t alignment, size_t alignmentOffset,
//	const char* pName, int flags, unsigned debugFlags, const char* file, int line)
//{
//	// doesn't support alignment
//	operator delete[](ptr);
//}

template<typename Type>
struct VecOfVec: public std::vector<std::vector<Type>> {};

class EntityManager
{
public:
	using ComponentBitSet= std::bitset<32>; // 
	using EntityBitSet = std::bitset<32>; // 

	std::vector<Entity*> entities;
	std::vector<std::vector<std::unique_ptr<Component>>*> components;


	ComponentBitSet componentBitSet;
	EntityBitSet entityBitSet;
public:
	EntityManager()
	{

	}
	~EntityManager()
	{
	}

	void CreateEntity()
	{
		entities.push_back(new Entity());
	}

	template<typename Type>
	bool HasComponent() const
	{
		return componentBitSet[GetComponentId<Type>()];
	}

	template<class CompType>
	void AddComponent(int id)
	{
		// If given component was never created.
		if (!HasComponent<CompType>())
		{
			components.emplace_back(new std::vector<std::unique_ptr<Component>>());
		}
		//int test = GetComponentId<CompType>() - 1;
		if(components[GetComponentId<CompType>() - 1])
		{
			if (!entities[id]->HasComponent<CompType>())
			{
				CompType* pTest(new CompType());
				pTest->SetOwnerId(id);

				int currentIndex = components[GetComponentId<CompType>() - 1]->size();
				pTest->SetCompId(currentIndex);

				std::unique_ptr<Component> ptr{ pTest };
				components[GetComponentId<CompType>() - 1]->push_back(std::move(ptr));
				componentBitSet[GetComponentId<CompType>()] = true;
				entities[id]->AddComponent<CompType>(pTest);
			}
		}
	}

	template<class Type>
	void Test()
	{
		std::vector<Type>* testVec = new std::vector<Type>();
		if (testVec)
			cout << "Success" << endl;
		delete testVec;
	}

	void RunTest()
	{
		for (unsigned int i = 0; i < components.size(); ++i)
		{
			for (unsigned int j = 0; j < components[i]->size(); ++j)
			{
				// i: ComponentTypeId
				// j: 
				components.at(i)->at(j)->Print();
			}

			cout << endl << endl;
		}
	}

	void Clear()
	{
		for (auto& entity : entities)
		{
			delete entity;
			entity = nullptr;
		}
		
		for (std::vector<std::unique_ptr<Component>>* pComponent : components)
		{
			for (unsigned int i = 0; i < pComponent->size(); ++i)
			{
				delete &pComponent[i];
			}
				
		}
		components.clear();
	}
};

int main()
{
	//cout << "Tranform: "	<< GetComponentId<Transform>()	<< endl;
	//cout << "Health: "		<< GetComponentId<Health>()		<< endl;
	//cout << "Speed: "		<< GetComponentId<Speed>()		<< endl;
	//cout << "Sound: "		<< GetComponentId<Sound>()		<< endl;
	//cout << endl;

	EntityManager manager;

	manager.CreateEntity(); // 0
	manager.CreateEntity(); // 1
	manager.CreateEntity(); // 2
	manager.CreateEntity(); // 3
	
	manager.AddComponent<Transform>(0);
	manager.AddComponent<Speed>(2);
	manager.AddComponent<Transform>(3);
	manager.AddComponent<Health>(0);
	manager.AddComponent<Sound>(2);
	manager.AddComponent<Speed>(0);
	manager.AddComponent<Sound>(0);
	manager.AddComponent<Sound>(1);
	manager.AddComponent<Speed>(1);

	manager.AddComponent<Health>(1);


	manager.AddComponent<Sound>(3);
	manager.AddComponent<Speed>(3);

	manager.RunTest();
	manager.Clear();

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