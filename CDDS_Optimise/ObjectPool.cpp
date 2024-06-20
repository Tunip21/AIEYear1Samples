#include "ObjectPool.h"
template <class T>
ObjectPool<T>::ObjectPool(unsigned int size)
	: m_size(size), m_data(new T[size]), m_active(new bool[size]) 
{
	for (int n = 0; n < m_size; ++n)
	{
		m_active[n] = false;
		m_data[n] = new T;
	}
}

template <class T>
ObjectPool<T>::~ObjectPool()
{
	delete[] m_data; 
	delete[] m_active;
}

ObjectPool<class T>* ObjectPool<class T>::allocate()
{
	for (int n = 0; n < m_size; ++n)
	{
		if (m_active[n] == false)
		{
			m_active[n] = true;
			//return &m_data[n];
		}
	}
	return nullptr;
}

template<class T>
void ObjectPool<T>::deallocate(int n)
{
	m_active[n] = false;
}

