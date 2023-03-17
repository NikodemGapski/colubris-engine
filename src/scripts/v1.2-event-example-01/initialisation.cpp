#include "scene_manager.hpp"
#include "event.hpp"

// event listener callback function
void callback(Event* event) {
	std::cout<<event->get_name()<<" haha!\n";
	std::cout<<"btw, the secret value is "<<event->get_data<int>()<<'\n';
}

struct B {
	int v;
	B(int v) : v(v) {}
};

// another callback listener
void callback2(Event* event) {
	std::string message;
	if(event->has_data()) {
		message = "This event (" + event->get_name() + ") does have data.\n";
	}else {
		message = "This event (" + event->get_name() + ") does NOT have any data.\n";
		event->get_data<B>();
	}
	std::cout<<message;
}

class A {
public:
	// instance-specific value
	int value;
	// instance-specific callback method
	void callback(Event* event) {
		std::cout<<event->get_name()<<" in A! "<<value<<'\n';
	}
	// add instance-specific listener
	void listen() {
		// add the callback listener (note the use of a lambda function)
		Event::listen("my event", [this](Event* event) {
			this->callback(event);
		});
	}
};

void SceneManager::instantiate_custom_objects() {
	// add callback listeners
	Event::listen("my event", callback);
	Event::listen("my event", callback2);
	Event::listen("no data event", callback2);
	// add A instance listener
	A* a = new A(); a->value = -5;
	a->listen();
	// emit the first event with some data
	int v = 3;
	Event::emit("my event", v);
	// emit the second event with no data
	Event::emit("no data event");
}