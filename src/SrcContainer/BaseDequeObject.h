#pragma  once

#ifndef C_BASE_DEQUE_OBJECT_H
#define C_BASE_DEQUE_OBJECT_H 

#include <functional>
#include <algorithm>
#include <stdint.h>
#include <iostream> 
#include <string> 
#include <iterator>
#include <assert.h>
#include <deque>



template <class T> class CDequeObjectContainer
{

public:
	CDequeObjectContainer()  { std::cout << "[CDequeObjectContainer::CDequeObjectContainer]" << "\n"; }
	~CDequeObjectContainer() { /*std::cout << "[CDequeObjectContainer::~CDequeObjectContainer]" << "\n";*/ }

public:

	std::deque<T> &	GetDeque()						{ return m_ObjectDeque; }
	void			Pop_front()						{ return m_ObjectDeque.pop_front(); }
	int				Size()							{ return m_ObjectDeque.size(); }
	bool			Empty()							{ return m_ObjectDeque.empty(); }
	void			Push_back(const T & CObject)	{ m_ObjectDeque.push_back(CObject); }
	void			SetDeque(std::deque<T> Val)		{ m_ObjectDeque = Val; }
	T &				GetObjectIndex(int Index);
public:


private:
	std::deque<T> m_ObjectDeque;
};



template <class T> T & CDequeObjectContainer<T>::GetObjectIndex(int Index)
{
	assert(Index < Size() && Index >= 0);

	return m_ObjectDeque[Index];
}



#endif  