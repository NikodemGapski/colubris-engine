#include "event_queue.hpp"
#include "event.hpp"

void EventQueue::add_listener(std::function<void(Event*)> listener) {
	listeners.push_back(listener);
}
void EventQueue::add_event(Event* event) {
	events.push_back(event);
}
void EventQueue::handle_events() {
	// create safe copies and clear previous events
	auto listeners_copy = listeners;
	auto events_copy = events;
	events.clear();

	// loop through events and call listeners on each one
	for(auto event : events_copy) {
		for(auto listener : listeners_copy) {
			listener(event);
		}
	}

	// deallocate previous events
	for(auto event : events_copy) {
		delete event;
	}
}