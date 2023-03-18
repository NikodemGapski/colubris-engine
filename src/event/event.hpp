#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include "event_queue.hpp"
#include "types.hpp"

class Event {
// ----- NON-STATIC MEMBERS -----
public:
	// delete the event and deallocate the data
	~Event();
	// return the name of the event
	std::string get_name() const;
	// return the pointer to the event data
	template<typename T>
	T get_data() const;
	// checks if the event carries any data
	bool has_data() const;

private:
	// create a new event with the specified name and a pointer to the event data
	// along with a function for its deletion
	Event(std::string name, void* data, std::function<void()> delete_data);
	
	std::string name;
	void* data;
	// data deallocation function (type-specific, needed because deleting a void pointer is undefined)
	std::function<void()> delete_data;

// ----- STATIC MEMBERS -----
public:
	// emit an event with the specified name and event's data
	template<typename T>
	static void emit(std::string name, T data);
	// emit an event with the specified name and no data
	static void emit(std::string name);
	// attach a listener callback function to the event with the specified name
	static void listen(std::string name, std::function<void(Event*)> callback);

private:
	static Dictionary<EventQueue*> event_queues;
	// handle events on every event queue
	static void handle_events();

// ----- FRIENDS -----
	friend class SceneManager;
};

// ----- TEMPLATE IMPLEMENTATIONS -----
#include "event_templates.hpp"