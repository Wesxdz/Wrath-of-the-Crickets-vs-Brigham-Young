#pragma once

class slComponent;

#include <list>
#include <SFML\Window.hpp>

/*
A base class for creating entities
*/
class slEntity
{
public:
	std::list<slComponent*> components;
public:
	~slEntity();
	void AddComponent(slComponent*);

	template <class T> T* GetComponent() const;
};

template <class T> T* slEntity::GetComponent() const
{
	for (auto c : components)
	{
		if (!c) continue;
		if (typeid(T) == typeid(*c))
		{
			return static_cast<T*> (c);
		}
	}
	return nullptr;
}

