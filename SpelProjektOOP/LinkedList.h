#pragma once

template<typename T>
class Node
{
	private:
	Node<T>* prev_ = nullptr;
	Node<T>* next_ = nullptr;

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
			node->next = this;
			node->prev = prev_;
			if (node->prev != nullptr) 
				node->prev->next = node;
		}

		prev_ = node;
	}

	void append(Node<T>* node)
	{
		if (node != nullptr)
		{
			node->prev = this
				node->next = next_;
			if (node->next != nullptr) 
				node->next->prev = node; 
		}

		next_ = node;
	}

	void remove()
	{
		if (prev_ != nullptr)
			prev_->next = next_;
		if (next_ != nullptr)
			next_->prev = prev_;
	}
	
	Node<T>* getPrev() const
	{
		return prev_;
	}

	Node<T>* getNext() const
	{
		return next_;
	}
};

template<typename T>
class LinkedList
{
	private:
	Node<T> startNode_;

	public:

	Node<T>* getFirst() const
	{
		return startNode_.getNext();
	}

	void insertFirst(Node<T>* node)
	{
		startNode_.append(node);
	}
};

