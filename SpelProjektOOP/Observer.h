#pragma once

template<typename Event, typename Context>
class Observer
{
	public:
	Observer();
	virtual ~Observer();

	virtual void onNotify(Event event, Context context) = 0;
};


template<typename Event, typename Context>
Observer<Event, Context>::Observer()
{}

template<typename Event, typename Context>
Observer<Event, Context>::~Observer()
{}