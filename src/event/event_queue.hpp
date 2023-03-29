#pragma once
#include <functional>
#include <vector>

class Event;

class EventQueue {
public:
	// add a new listener to the list
	void add_listener(std::function<void(Event*)> listener);
	// add a new event to the event list
	void add_event(Event* event);
	// execute all listeners' functions for all events
	void handle_events();

protected:
	std::vector<std::function<void(Event*)> > listeners;
	std::vector<Event*> events;
};