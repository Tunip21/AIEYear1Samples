#pragma once

template <class T>
class ObjectPool {
public:
	ObjectPool(unsigned int size);
	~ObjectPool();
	ObjectPool* allocate();
	void deallocate(int n);
private:
	unsigned int m_size = 0;
	T* m_data = nullptr;
	bool* m_active = nullptr;
};
