#pragma once

#include <iostream>
using namespace std;

template<typename T>
class SortedList
{
	private:
	T* elements;
	int nrOf;
	int cap;
	void expand()
	{
		cap += 10;
		T* newList = new T[cap];

		for (int i = 0; i < nrOf; i++)
		{
			newList[i] = elements[i];
		}

		delete[] elements;
		elements = newList;
	}

	public:
	int check(const T element) const
	{
		bool found = false;
		int pos = -1;
		int low = 0;
		int high = nrOf;
		int check = 0;

		while (low <= high && !found)
		{
			check = (high + low) / 2;

			if (elements[check] == element)
			{
				pos = -1;
				found = true;
			}
			else if (elements[check] < element)
			{
				low = check + 1;
				pos = check + 1;
			}
			else if (elements[check] > element)
			{
				high = check - 1;
				pos = check;
			}
		}

		return pos;
	}
	int find(const T element) const
	{
		int pos = -1;
		int low = 0;
		int high = nrOf;
		int check = 0;

		while (nrOf > 0 && low <= high && pos == -1)
		{
			check = (high + low) / 2;

			if (elements[check] == element)
			{
				pos = check;
			}
			else if (elements[check] < element)
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

	SortedList()
	{
		nrOf = 0;
		cap = 10;
		elements = new T[cap];
	}
	virtual ~SortedList() { delete[] elements; }
	
	int length() const
	{
		return nrOf;
	}

	bool add(const T element)
	{
		bool added = false;
		int pos = check(element);

		if (pos != -1)
		{
			if (nrOf >= cap) expand();
			if (pos > nrOf)
			{
				elements[nrOf++] = element;
			}
			else
			{
				for (int i = nrOf; i > pos; i--)
				{
					elements[i] = elements[i - 1];
				}
				
				elements[pos] = element;
				nrOf++;
			}
			added = true;
		}

		return added;
	}

	bool exists(const T element) const
	{
		return find(element) != -1;
	}

	void remove(const T element)
	{
		int pos = find(element);

		if (pos != -1)
		{
			for (int i = pos; i < nrOf - 1; i++)
			{
				elements[i] = elements[i + 1];
			}
			nrOf--;
		}
	}


	T& operator[](size_t pos)
	{
		return elements[pos];
	}
	const T& operator[](size_t pos) const
	{
		return elements[pos];
	}
};

template<typename T>
class List
{
	private:
	T* elements;
	int nrOf;
	int cap;
	void expand()
	{
		cap += 10;
		T* newList = new T[cap];

		for (int i = 0; i < nrOf; i++)
		{
			newList[i] = elements[i];
		}

		delete[] elements;
		elements = newList;
	}
	public:

	int find(const T element) const
	{
		int pos = -1;

		for (size_t i = 0; i < nrOf && pos == -1; i++)
		{
			if (elements[i] == element)
			{
				pos = i;
			}
		}

		return pos;
	}

	List()
	{
		nrOf = 0;
		cap = 10;
		elements = new T[cap];


	}
	virtual ~List() { delete[] elements; }

	int length() const
	{
		return nrOf;
	}

	void add(const T element)
	{
		if (nrOf >= cap) expand();
		elements[nrOf++] = element;
	}

	bool exists(const T element) const
	{
		return find(element) != -1;
	}

	void remove(int pos)
	{
		for (int i = pos; i < nrOf - 1; i++)
		{
			elements[i] = elements[i + 1];
		}
		nrOf--;
	}

	void remove(const T element)
	{
		int pos = find(element);

		if (pos != -1)
		{
			for (int i = pos; i < nrOf - 1; i++)
			{
				elements[i] = elements[i + 1];
			}
			nrOf--;
		}
	}
	
	T& operator[](size_t pos)
	{
		return elements[pos];
	}
	const T& operator[](size_t pos) const
	{
		return elements[pos];
	}

};
