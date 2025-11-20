#ifndef SAFEQUEUE_HPP
#define SAFEQUEUE_HPP

#include <windows.h>
#include <WindowsX.h>
#include <iostream>


template <typename Type>
class SafeQueue
{
public:
	SafeQueue(unsigned int _size);
	~SafeQueue();

	void Push(void* _data);
	void Pop();

	Type operator[](unsigned int index);

private:
	unsigned int m_size;
	unsigned int m_capacity;
	bool m_isFull;
	Type* m_elements;

	LPCRITICAL_SECTION m_CS;
	bool isCSActive;

};

/////////////////////////////////////////////////////////////////////////

template <typename Type>
inline SafeQueue<Type>::SafeQueue(unsigned int _size) : m_capacity(_size), m_size(0), m_CS(new CRITICAL_SECTION), isCSActive(false)
{
	InitializeCriticalSection(m_CS);

	m_elements = new Type[m_capacity];
	for (int i = 0; i < m_capacity; i++)
	{
		m_elements[i] = Type();
	}
}

template<typename Type>
inline SafeQueue<Type>::~SafeQueue()
{
	LeaveCriticalSection(m_CS);
	DeleteCriticalSection(m_CS);

	delete[] m_elements;
}

template<typename Type>
inline void SafeQueue<Type>::Push(void* _data)
{
	if (isCSActive)
	{
		std::cout << "[SafeQueue::Push() : Couldn't push data ; it is currently under Critical Section !]\n";
		return;
	}

	if (TryEnterCriticalSection(m_CS) == false)
	{
		std::cout << "[SafeQueue::Push() : Couldn't enter Critical Section !]\n";
		return;
	}

	EnterCriticalSection(m_CS);
		isCSActive = true;
		if (reinterpret_cast<Type>(_data) == false || m_isFull == true)
			return;
	
		m_elements[0] = reinterpret_cast<Type>(_data);
		if (m_size + 1 < m_capacity)
			m_size++;
		else
			m_isFull = true;
	LeaveCriticalSection(m_CS);
	isCSActive = false;
}

template<typename Type>
inline void SafeQueue<Type>::Pop()
{
	if (isCSActive)
	{
		std::cout << "[SafeQueue::Pop() : Couldn't pop data ; it is currently under Critical Section !]\n";
		return;
	}

	if (TryEnterCriticalSection(m_CS) == false)
	{
		std::cout << "[SafeQueue::Pop() : Couldn't enter Critical Section !]\n";
		return;
	}

	EnterCriticalSection(m_CS);
		isCSActive = true;
		delete m_elements[0];

		for (int i = 1; i <= m_size; i++)
		{
			if ((i + 1) > m_capacity)
				continue;
			m_elements[i] = m_elements[i + 1];
		}
	LeaveCriticalSection(m_CS);
	isCSActive = false;
}

template <typename Type>
inline Type SafeQueue<Type>::operator[](unsigned int index)
{
	if (isCSActive)
	{
		std::cout << "[SafeQueue::operator[] : Couldn't access data ; it is currently under Critical Section !]\n";
		return Type();
	}

	if (TryEnterCriticalSection(m_CS) == false)
	{
		std::cout << "[SafeQueue::operator[] : Couldn't enter Critical Section !]\n";
		return Type();
	}

	EnterCriticalSection(m_CS);
		isCSActive = true;
		if (index < 0 || index > m_size)
			return Type();
		Type toReturn = m_elements[index];
	LeaveCriticalSection(m_CS);
	isCSActive = false;
	
	return toReturn;
}

#endif // SAFEQUEUE_HPP