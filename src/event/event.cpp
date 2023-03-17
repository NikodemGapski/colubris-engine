#include "event.hpp"

std::unordered_map<std::string, EventQueue*> Event::event_queues;

Event::Event(std::string name, void* data, std::function<void()> delete_data) : name(name), data(data), delete_data(delete_data) {}
Event::~Event() {
	if(has_data()) {
		delete_data();
	}
}

std::string Event::get_name() const {
	return name;
}
bool Event::has_data() const {
	return data != NULL;
}

void Event::listen(std::string name, std::function<void(Event*)> callback) {
	if(event_queues.find(name) == event_queues.end()) {
		// create a new event queue
		event_queues.insert({name, new EventQueue});
	}
	// add a new listener to the queue
	event_queues[name]->add_listener(callback);
}

void Event::emit(std::string name) {
	if(event_queues.find(name) == event_queues.end()) {
		// create a new event queue
		event_queues.insert({name, new EventQueue()});
	}
	// add a new event to the queue with its data and a type-specific deallocation function
	event_queues[name]->add_event(new Event(name, NULL, [](){}));
}

void Event::handle_events() {
	for(auto queue : event_queues) {
		queue.second->handle_events();
	}
}