#include <cstddef>
#include "AList.h"

namespace Zaxis{ namespace Engine{ namespace Data
{
	template<class T>
	AList<T>::AList()
	{
		front = 0;
		back = 0;
		_size = 0;
		for (int i = 0; i < MAXLISTSIZE; i++)
		{
			list[i] = NULL;
		}
	}


	template<class T>
	AList<T>::~AList()
	{
	}

	template<class T>
	int AList<T>::NextIndex(int val)
	{
		int idx = (val + 1) % MAXLISTSIZE;
		return idx;
	}

	template<class T>
	int AList<T>::PrevIndex(int val)
	{
		int idx = 0;
		if (val < 0)
		{
			idx = MAXLISTSIZE - 1;
		}
		else
		{
			idx = (val - 1) % MAXLISTSIZE;
		}
		return idx;
	}

	template<class T>
	T* AList<T>::push_back(T item)
	{
		int nid = NextIndex(back);
		if (front != NextIndex(back))
		{
			list[back] = &item;
			back = NextIndex(back);
			_size++;
		}

		return list[PrevIndex(back)];
	}

	template<class T>
	T* AList<T>::push_front(T item)
	{
		if (back != PrevIndex(front))
		{
			front = PrevIndex(front);
			list[front] = &item;
			_size++;
		}

		return list[front];
	}

	template<class T>
	T AList<T>::pop_front()
	{
		T* item = NULL;
		if (front != back)
		{
			item = list[front];
			list[front] = NULL;
			front = NextIndex(front);
			_size--;
		}

		return (*item);
	}

	template<class T>
	T AList<T>::pop_back()
	{
		T* item = NULL;
		if (front != back)
		{
			back = PrevIndex(back);
			item = list[back];
			list[back] = NULL;
			_size--;
		}

		return (*item);
	}

	template<class T>
	T AList<T>::RmItem(int idx)
	{
		T* item;
		if (list[idx] != NULL)
		{
			item = list[idx];
			while (list[NextIndex(idx)] != NULL)
			{
				list[idx] = list[NextIndex(idx)];
				list[NextIndex(idx)] = NULL;
				idx = NextIndex(idx);
			}
			back = PrevIndex(back);
		}

		return (*item);
	}

	template<class T>
	T AList<T>::GetPos(int idx)
	{
		return (*list[idx)];
	}

	template<class T>
	int AList<T>::Front()
	{
		return front;
	}

	template<class T>
	int AList<T>::Back()
	{
		return PrevIndex(back);
	}

	template<class T>
	int AList<T>::size()
	{
		return _size;
	}

} } }// End namespace Zaxis::Engine::Data
