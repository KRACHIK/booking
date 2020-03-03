#pragma  once

#ifndef C_BASEGAMEOBJECT_H
#define C_BASEGAMEOBJECT_H 

#include <functional>
#include <algorithm>
#include <stdint.h>
#include <iostream> 
#include <string>
#include <iterator>
#include <assert.h>
#include <map> 
#include <deque>



template <class T> class CObjectContainerDequeInMap
{
public:

	typedef typename std::map<int, std::deque<T>>::iterator iterator;
	 
	CObjectContainerDequeInMap() {}
	~CObjectContainerDequeInMap() {}

#if 0

	bool FindObjectByKey(int Key);

	bool Remove(int Key)
	{
		auto it = std::find_if(m_ObjectMap.begin(), m_ObjectMap.end(),
			[&Key](const std::pair<int, T> &p) {
			return p.first == Key;
		});

		if (it != m_ObjectMap.end())
		{
			m_ObjectMap.erase(it);
			return true;
		}

		return false;
	}

	T GetClonObject(int Key);

	T & GetObject(int Key)
	{
		std::map<int, T>::iterator m_iterator = std::find_if(m_ObjectMap.begin(), m_ObjectMap.end(), [&Key](const std::pair<int, T> &p)
		{
			return p.first == Key;
		});

		return m_iterator;
	}

	void Insert(int Key, const T & CObject);

	void Insert(int Key, T & CObject);

	iterator GetIteratorObject(int ObjectKey)
	{
		std::map<int, T>::iterator m_iterator = std::find_if(m_ObjectMap.begin(), m_ObjectMap.end(),
			[&ObjectKey](const std::pair<int, T> &p) {
			return p.first == ObjectKey;
		});
		return m_iterator;
	}


	std::map<int, T> GetCloneMap() { return m_ObjectMap; }

	void Clear() { m_ObjectMap.clear(); }

	std::map<int, T> & GetMap() { return m_ObjectMap; }
#endif

	iterator Begin() { return m_ObjectMap.begin(); }

	iterator End() { return m_ObjectMap.end(); }
	/* 
	iterator GetIteratorObject(int ObjectKey)
	{
		std::map<int, std::deque<T>>::iterator m_iterator = std::find_if(m_ObjectMap.begin(), m_ObjectMap.end(),
			[&ObjectKey](const std::pair<int, std::deque<T>> &p) {
			return p.first == ObjectKey;
		});
		return m_iterator;
	}
		 */
	void PushBackDeque(int ObjectKey,  std::deque<T> & Arr)
	{
		//std::map<int, std::deque<T>>::iterator  it  = GetIteratorObject(int ObjectKey);
		std::map<int, std::deque<T>>::iterator m_iterator = std::find_if(m_ObjectMap.begin(), m_ObjectMap.end(),
			[&ObjectKey](const std::pair<int, std::deque<T>> &p) {
			return p.first == ObjectKey;
		});
		   
		if (m_iterator != End())
		{
			for (auto itArr : Arr)
			{
				m_iterator->second.push_back(itArr);
			}
		}
		else
		{
			m_ObjectMap.insert(std::pair<int, std::deque<T>&>(ObjectKey, Arr));
		}
	}


private:
	
	std::map<int, std::deque<T>> m_ObjectMap;
};



template <class T> class CMultimapCounterContainer
{

	class CCounters{

	public:
		CCounters(){}

		CCounters(T TObject)
			: _TObject(TObject)
			, _Count(1)
		{
		}

		T	_TObject;
		int	_Count = 0;
	};

	typedef typename std::map<int, CCounters>::iterator iterator;

	std::map<int, CCounters> _ObjectMap;

public:
	CMultimapCounterContainer(std::map<int, CCounters> Map)
	{
		_ObjectMap = Map;
	}


	CMultimapCounterContainer(){}

	~CMultimapCounterContainer() {}

	void Add(int Key, const T & CObject)
	{
		CCounters ObjectCounters(CObject);

		if (!FindObjectByKey(Key))
		{
			// Add
			_ObjectMap.insert(std::pair<int, CCounters>(Key, ObjectCounters));
		}
		else
		{
			// inc
			auto it = GetIteratorObject(Key);

			it->second._Count++;

		}

	}

	bool FindObjectByKey(int Key){

		auto it = std::find_if(_ObjectMap.begin(), _ObjectMap.end(),
			[&Key](const std::pair<int, CCounters> &p){
			return p.first == Key;
		});

		if (it != _ObjectMap.end())
			return true;

		return false;
	}

	iterator GetIteratorObject(int ObjectKey)
	{
		std::map<int, CCounters>::iterator it = std::find_if(_ObjectMap.begin(), _ObjectMap.end(), [&ObjectKey](const std::pair<int, CCounters> &p){return p.first == ObjectKey; });
		return it;
	}

	size_t Size() { return _ObjectMap.size(); }

	CMultimapCounterContainer GetPopularValues(int RepeatCount)
	{

#if 0	// Это не работает
		std::map<int, CCounters> TempGoodValuesMap;
		remove_copy_if(_ObjectMap.begin(), _ObjectMap.end(),
			std::inserter(TempGoodValuesMap,
			TempGoodValuesMap.end()),
			[=](const std::pair<int, CCounters> &A){
			return A.second._Count >= RepeatCount;
		});
		_ObjectMap.swap(TempGoodValuesMap);
#endif
		std::map<int, CCounters> TempGoodValuesMap;

		for (auto it = _ObjectMap.begin(); it != _ObjectMap.end(); it++)
		{
			if (it->second._Count >= RepeatCount)
				TempGoodValuesMap.insert(std::pair<int, CCounters>(it->first, it->second));
		}

		return CMultimapCounterContainer(TempGoodValuesMap);
	}

	iterator Begin() { return  _ObjectMap.begin(); }

	iterator End(){ return  _ObjectMap.end(); }
};

template <class T> class CObjectContainerMap
{
public:

	typedef typename std::map<int, T>::iterator iterator;

	CObjectContainerMap()  {}
	~CObjectContainerMap() {}

	bool FindObjectByKey(int Key);

	bool Remove(int Key)
	{
		auto it = std::find_if(m_ObjectMap.begin(), m_ObjectMap.end(),
			[&Key](const std::pair<int, T> &p){
			return p.first == Key;
		});

		if (it != m_ObjectMap.end())
		{
			m_ObjectMap.erase(it);
			return true;
		}

		return false;
	}

	T GetClonObject(int Key);

	T & GetObject(int Key)
	{
		std::map<int, T>::iterator m_iterator = std::find_if(m_ObjectMap.begin(), m_ObjectMap.end(), [&Key](const std::pair<int, T> &p)
		{
			return p.first == Key;
		});

		return m_iterator;
	}

	void Insert(int Key, const T & CObject);

	void Insert(int Key, T & CObject);

	iterator GetIteratorObject(int ObjectKey)
	{
		std::map<int, T>::iterator m_iterator = std::find_if(m_ObjectMap.begin(), m_ObjectMap.end(),
			[&ObjectKey](const std::pair<int, T> &p){
			return p.first == ObjectKey;
		});
		return m_iterator;
	}

	iterator Begin() { return m_ObjectMap.begin(); }

	iterator End(){ return m_ObjectMap.end(); }

	std::map<int, T> GetCloneMap() { return m_ObjectMap; }

	void Clear() { m_ObjectMap.clear(); }

	std::map<int, T> & GetMap(){ return m_ObjectMap; }

private:

	std::map<int, T> m_ObjectMap;

};

template <class T> T CObjectContainerMap<T>::GetClonObject(int Key)
{
	std::map<int, T>::iterator m_iterator = std::find_if(m_ObjectMap.begin(), m_ObjectMap.end(),
		[&Key](const std::pair<int, T> &p){
		return p.first == Key;
	});

	return m_iterator->second;
}

template <class T> bool CObjectContainerMap<T>::FindObjectByKey(int Key)
{
	if (m_ObjectMap.empty())
		return false;

	auto it = std::find_if(m_ObjectMap.begin(), m_ObjectMap.end(),
		[&Key](const std::pair<int, T> &p){
		return p.first == Key;
	});

	if (it != m_ObjectMap.end())
		return true;

	return false;
}

template <class T> void CObjectContainerMap<T>::Insert(int Key, const T & CObject)
{
	m_ObjectMap.insert(std::pair<int, T>(Key, CObject));
}

template <class T> void CObjectContainerMap<T>::Insert(int Key, T& CObject)
{
	m_ObjectMap.insert(std::pair<int, T&>(Key, CObject));
}



template <class T> class CObjectStringContainerMap
{
public:

	typedef typename std::map<std::string, T>::iterator iterator;

	CObjectStringContainerMap()  {}
	~CObjectStringContainerMap() {}

	bool FindObjectByKey(std::string Key);
	bool Remove(std::string Key);

	T GetClonObject(std::string Key);

	T & GetObject(std::string Key)
	{
		std::map<std::string, T>::iterator m_iterator = std::find_if(
			m_ObjectMap.begin(), m_ObjectMap.end(),
			[&Key](const std::pair<std::string, T> &p)
		{
			return p.first == Key;
		});

		return m_iterator;
	}

	void Insert(std::string Key, const T & CObject);
	void Insert(std::string Key, T & CObject);

	iterator GetIteratorObject(std::string ObjectKey)
	{
		std::map<std::string, T>::iterator m_iterator = std::find_if(m_ObjectMap.begin(), m_ObjectMap.end(),
			[&ObjectKey](const std::pair<std::string, T> &p){
			return p.first == ObjectKey;
		});
		return m_iterator;
	}

	std::map<std::string, T> GetCloneMap() { return m_ObjectMap; }

	void Clear() { m_ObjectMap.clear(); }

	std::map<std::string, T> & GetMap() { return m_ObjectMap; }

private:

	std::map<std::string, T> m_ObjectMap;

};

template <class T> bool CObjectStringContainerMap<T>::Remove(std::string Key)
{
	auto it = std::find_if(m_ObjectMap.begin(), m_ObjectMap.end(), [&Key](const std::pair<std::string, T> &p){
		return p.first == Key;
	});

	if (it != m_ObjectMap.end())
	{
		m_ObjectMap.erase(it);

		return true;
	}

	return false;
}

template <class T> T CObjectStringContainerMap<T>::GetClonObject(std::string Key)
{
	std::map<std::string, T>::iterator m_iterator = std::find_if(m_ObjectMap.begin(), m_ObjectMap.end(),
		[&Key](const std::pair<std::string, T> &p){
		return p.first == Key;
	});

	return m_iterator->second;
}

template <class T> bool CObjectStringContainerMap<T>::FindObjectByKey(std::string Key)
{
	auto it = std::find_if(m_ObjectMap.begin(), m_ObjectMap.end(),
		[&Key](const std::pair<std::string, T> &p){
		return p.first == Key;
	});

	if (it != m_ObjectMap.end())
		return true;

	return false;
}

template <class T> void CObjectStringContainerMap<T>::Insert(std::string Key, const T &CObject)
{
	m_ObjectMap.insert(std::pair<std::string, const T&>(Key, CObject));
}

template <class T> void CObjectStringContainerMap<T>::Insert(std::string Key, T &CObject)
{
	m_ObjectMap.insert(std::pair<std::string, T&>(Key, CObject));
}

  
#endif   


