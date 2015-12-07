#include "LinkedList.h"


template<typename T>

template<typename T>
LinkedList<T>::LinkedList()
{}
template<typename T>
LinkedList<T>::~LinkedList()
{
	Node<T>* node = getFirst();
	Node<T>* next = nullptr;
	while (node != nullptr)
	{
		next = node->getNext();
		delete node;
		node = next;
	}
}


template<typename T>
void LinkedList<T>::clear()
{
	Node<T>* node = getFirst();
	Node<T>* next = nullptr;
	while (node != nullptr)
	{
		next = node->getNext();
		node->remove();
		delete node;
		node = next;
	}
}


template<typename T>
Node<T>* LinkedList<T>::getFirst() const
{
	return startNode_.getNext();
}
template<typename T>
void LinkedList<T>::insertFirst(Node<T>* node)
{
	startNode_.append(node);
}
template<typename T>
void LinkedList<T>::insertFirst(T data)
{
	startNode_.append(new Node<T>(data));
}
