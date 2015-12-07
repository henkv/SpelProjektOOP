#pragma once


template<typename T, int MAX = 10>
class Queue
{
	private:
	int tail_;
	int head_;
	int length_;
	T queue_[MAX];

	public:
	Queue();
	virtual ~Queue();

	bool pop(T& element);
	void push(T element) throw(...);
};


template<typename T, int MAX>
Queue<T, MAX>::Queue()
{
	length_ = 0;
	head_ = 0;
	tail_ = 0;
}

template<typename T, int MAX>
Queue<T, MAX>::~Queue()
{}



template<typename T, int MAX>
bool Queue<T, MAX>::pop(T& element)
{
	bool notEmpty = length_ > 0;

	if (notEmpty)
	{
		element = queue_[head_];
		++head_ %= MAX;
		length_--;
	}

	return notEmpty;
}

template<typename T, int MAX>
void Queue<T, MAX>::push(T element) throw(...)
{

	if (length_ == MAX)
	{
		throw "Tail ate the head.";
	}

	queue_[tail_] = element;
	++tail_ %= MAX;
	length_++;
}