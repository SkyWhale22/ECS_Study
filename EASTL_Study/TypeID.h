#pragma once

template<typename BaseType>
class TypeID
{
private:
	static unsigned int m_nextId;
public:
	template<typename Type>
	static unsigned int GetId()
	{
		static const unsigned int id = ++m_nextId;
		return id;
	}
};

template<typename BaseType>
unsigned int TypeID<BaseType>::m_nextId = 0;