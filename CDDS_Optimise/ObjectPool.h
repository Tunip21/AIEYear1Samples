#pragma once
template <class T>
class ObjectPool
{
	T* pool;
	int poolSize;

public:
    T& BeginOfArray()
    {
        int critterAlive = poolSize - 1;
        T alive = pool[critterAlive];
        for (int n = critterAlive; n > 0; --n)
        {
            pool[n] = pool[n - 1];
        }
        pool[0] = alive;
        return pool[0];
    }

    T& EndOfArray(int critterDead)
    {
        T dead = pool[critterDead];
        for (int n = critterDead; n < poolSize - 1; ++n) //altered
        {
            pool[n] = pool[n + 1];
        }
        pool[poolSize - 1] = dead;
        return pool[poolSize - 1];
    }

    ObjectPool(int numObjects)
    {
        pool = new T[numObjects];
        poolSize = numObjects;
    }

    ~ObjectPool()
    {
        delete[] pool;
    }

    T& operator[](int i)
    {
        return pool[i];
    }
};
