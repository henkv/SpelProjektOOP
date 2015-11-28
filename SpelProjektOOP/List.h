#pragma once
#include <iostream>
using namespace std;

template<typename T>
class List
{
	private:
	T** elements;
	size_t nrOf;
	size_t cap;
	void expand()
	{
		cap += 10;
		T** newList = new T*[cap];

		for (size_t i = 0; i < nrOf; i++)
		{
			newList[i] = elements[i];
		}

		delete[] elements;
		elements = newList;
	}
	int check(const T* element) const
	{
		bool found = false;
		int pos = 0;
		int low = 0;
		int high = nrOf;
		int check = 0;

		while (low <= high && !found)
		{
			check = (high + low) / 2;

			if (*elements[check] == *element)
			{
				found = true;
				pos = -2;
			}
			else if (*elements[check] < *element)
			{
				low = check + 1;
				pos = check;
			}
			else if (*elements[check] > *element)
			{
				high = check - 1;
				pos = check - 1;
			}
		}

		return pos;
	}
	int find(const T* element) const
	{
		int pos = -1;
		int low = 0;
		int high = nrOf;
		int check = 0;

		while (low <= high && pos == -1)
		{
			check = (high + low) / 2;

			if (*elements[check] == *element)
			{
				pos = check;
			}
			else if (*elements[check] < *element)
			{
				low = check + 1;
			}
			else
			{
				high = check - 1;
			}
		}

		return pos;
	}

	public:
	List()
	{
		nrOf = 0;
		cap = 10;
		elements = new T*[cap];
	}
	virtual ~List() { delete[] elements; }
	
	size_t length() const
	{
		return nrOf;
	}

	void add(T* element)
	{
		int pos = check(element);

		if (pos != -2)
		{
			if (nrOf >= cap) expand();

			if (pos == nrOf)
			{
				elements[nrOf++] = element;
			}
			else
			{
				for (int i = nrOf; i > pos; i--)
				{
					elements[i] = elements[i - 1];
				}
				elements[pos + 1] = element;
				nrOf++;
			}

		}
	}

	bool exists(const T* element) const
	{
		return find(element) != -1;
	}

	void remove(const T* element)
	{
		int pos = find(element);

		if (pos != -1)
		{
			nrOf--;
			for (size_t i = pos; i < nrOf; i++)
			{
				elements[i] = elements[i + 1];
			}
		}
	}

	T* operator[](size_t pos)
	{
		return elements[pos];
	}
	const T* operator[](size_t pos) const
	{
		return elements[pos];
	}

};

