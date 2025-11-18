#ifndef THREADQUEUE_HPP
#define THREADQUEUE_HPP

#include <windows.h>
#include <iostream>


template <typename Type>
class ThreadQueue
{
public:
	ThreadQueue(unsigned int _size);
	~ThreadQueue();

	void Push(void* _data);
	void Pop();

private:
	unsigned int m_size;
	unsigned int m_capacity;
	bool m_isFull;
	Type* m_elements;

	struct // m_CS
	{
		LPCRITICAL_SECTION self;
		bool isActive;
	} m_CS;
};

/////////////////////////////////////////////////////////////////////////

template <typename Type>
inline ThreadQueue<Type>::ThreadQueue(unsigned int _size) : m_size(_size)
{
	InitializeCriticalSection(m_CS.self);

	m_elements = new Type[m_size];
	for (int i = 0; i < m_size; i++)
	{
		m_elements[i] = Type();
	}
}

template<typename Type>
inline ThreadQueue<Type>::~ThreadQueue()
{
	LeaveCriticalSection(m_CS.self);
	DeleteCriticalSection(m_CS.self);

	delete[] m_elements;
}

template<typename Type>
inline void ThreadQueue<Type>::Push(void* _data)
{
	if (m_CS.isActive)
	{
		std::cout << "[ThreadQueue::Push() : Couldn't push data ; it is currently under Critical Section !]\n";
		return;
	}

	if (TryEnterCriticalSection(m_CS.self) == false)
	{
		std::cout << "[ThreadQueue::Push() : Couldn't enter Critical Section !]\n";
		return;
	}

	EnterCriticalSection(m_CS.self);
		m_CS.isActive = true;
		if (reinterpret_cast<Type>(data) == false || m_isFull == true)
			return -1;
	
		m_elements[m_size] = _data;
		if (m_size + 1 < m_capacity)
			m_size++;
		else
			m_isFull = true;
	LeaveCriticalSection(m_CS.self);
}

template<typename Type>
inline void ThreadQueue<Type>::Pop()
{
	if (m_CS.isActive)
	{
		std::cout << "[ThreadQueue::Pop() : Couldn't pop data ; it is currently under Critical Section !]\n";
		return;
	}

	if (TryEnterCriticalSection(m_CS.self) == false)
	{
		std::cout << "[ThreadQueue::Pop() : Couldn't enter Critical Section !]\n";
		return;
	}

	EnterCriticalSection(m_CS.self);
		delete m_elements[0];

		for (int i = 1; i <= m_size; i++)
		{
			if ((i + 1) > m_capacity)
				continue;
			m_elements[i] = m_elements[i + 1]
		}
	LeaveCriticalSection(m_CS.self);
}












#endif //THREADQUEUE_HPP