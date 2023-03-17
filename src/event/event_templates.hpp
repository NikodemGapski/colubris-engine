#pragma once
#include <iostream>
#include "event.hpp"

// return the pointer to the event data
template<typename T>
T Event::get_data() const {
	if(!has_data()) {
		std::cerr<<"Error: Event::get_data<T>(): the event has no data.\n";
		throw 2;
	}
	return *(T*)data;
}

// emit an event with the specified name and event's data
template<typename T>
void Event::emit(std::string name, T data) {
	if(event_queues.find(name) == event_queues.end()) {
		// create a new event queue
		event_queues.insert({name, new EventQueue()});
	}
	// allocate the data on the heap with the argument's values
	T* data_on_heap = new T(data);
	// add a new event to the queue with its data and a type-specific deallocation function
	event_queues[name]->add_event(new Event(name, (void*)data_on_heap, [data_on_heap]() {
		delete data_on_heap;
	}));
}