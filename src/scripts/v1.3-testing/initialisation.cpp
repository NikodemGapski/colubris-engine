#include "scene_manager.hpp"
#include "component_locator.hpp"
#include <iostream>

class MyComp {
	int counter;
	static int global_counter;
public:
	MyComp() : counter(global_counter++) {}
	void update(double dt) {
		std::cout << "My name is " << counter << ". [round " << dt << "]\n";
	}
};

int MyComp::global_counter = 0;

void nl() {
	std::cout << std::endl;
}

void locator_test() {
	ComponentLocator<MyComp> locator;
	locator.update(0); nl(); // Nothing
	locator.add(0);
	locator.add(1);
	locator.update(1); nl(); // 0, 1
	locator.add(2);
	locator.remove(0);
	locator.update(2); nl(); // 2, 1
	locator.set_active(2, false);
	locator.update(3); nl(); // 1
	locator.set_active(2, true);
	locator.update(4); nl(); // 1, 2

	locator.get(1).update(5); // 1
	locator.get(2).update(5); // 2
	try {
		locator.get(0).update(5); // throw
	} catch (...) {
		std::cout << "No entity 0 found.\n";
	}
}

void SceneManager::instantiate_custom_objects() {
	std::cout << "Hello there!\nObi-Wan Kenobi.\n";

}