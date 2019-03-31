#pragma once
class Component
{
protected:
	int ownerId;
	int componentTypeId;
	int componentId;

public:
	virtual ~Component() {};
	virtual void Print()
	{
		cout << "ownerId: " << ownerId << ",";
		cout << " typeId: " << componentTypeId << ",";
		cout << " componentId: " << componentId << ",";
	}

	void SetOwnerId(int id)
	{
		ownerId = id;
	}

	void SetCompId(int id)
	{
		componentId = id;
	}
};

class Transform : public Component
{
public:
	Transform()
	{
		this->componentTypeId = GetComponentId<Transform>();
	}

	virtual void Print() override
	{
		Component::Print();
		cout << " Component: Transform" << endl;
	}
};

class Speed : public Component
{
public:
	Speed()
	{
		this->componentTypeId = GetComponentId<Speed>();
	}

	virtual void Print() override
	{
		Component::Print();
		cout << " Component: Speed" << endl;
	}
};

class Health : public Component
{
public:
	Health()
	{
		this->componentTypeId = GetComponentId<Health>();
	}

	virtual void Print() override
	{
		Component::Print();
		cout << " Component: Health" << endl;
	}
};

class Sound : public Component
{
public:
	Sound()
	{
		this->componentTypeId = GetComponentId<Sound>();
	}

	virtual void Print() override
	{
		Component::Print();
		cout << " Component: Sound" << endl;
	}
};

