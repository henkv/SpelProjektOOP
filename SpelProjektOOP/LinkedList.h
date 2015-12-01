#pragma once

template<typename T>
class Node
{
	private:
	Node<T>* prev = nullptr;
	Node<T>* next = nullptr;

	public:
	T data;

	Node(T data = NULL)
	{
		this->data = data;
	}

	void prepend(Node<T>* node)
	{
		if (node != nullptr)
		{
			node->next = this;									// prev   node-->this // 
			node->prev = this->prev;							// prev<--node-->this //
			if (node->prev != nullptr) node->prev->next = node; // prev<->node-->this //
		}

		this->prev = node;									// prev<->node<->this // 
	}

	void append(Node<T>* node)
	{
		if (node != nullptr)
		{
			node->prev = this;									// this<--node   next // 
			node->next = this->next;							// this<--node-->next // 
			if (node->next != nullptr) node->next->prev = node; // this<--node<->next // 
		}

		this->next = node;									// this<->node<->next // 
	}

	void remove()
	{

		/*
			prev<->this<->next
			prev--------->next
			prev<-------->next
		*/
		if (this->prev != nullptr) this->prev->next = this->next; 
		if (this->next != nullptr) this->next->prev = this->prev;
	}
	
	Node<T>* getPrev() const
	{
		return prev;
	}

	Node<T>* getNext() const
	{
		return next;
	}
};

template<typename T>
class LinkedList
{
	private:
	Node<T> startNode;

	public:

	Node<T>* getFirst() const
	{
		return startNode.getNext();
	}

	void insertFirst(Node<T>* node)
	{
		startNode.append(node);
	}
};

