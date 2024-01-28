#pragma once

#include "component_locator_i.hpp"

#include <unordered_map>
#include <typeinfo> // typeid
#include <typeindex> // std::type_index
#include <memory> // std::unique_ptr

namespace colubris {

	class ComponentManager {
		using locator_ptr_t = std::unique_ptr<ComponentLocatorI>;
	public:
		/* Execute start methods on all component locators. */
		void start() {
			for (auto& it : locators) {
				it.second->start();
			}
		}
		/* Execute update methods on all component locators. */
		void update(double dt) {
			for (auto& it : locators) {
				it.second->update(dt);
			}
		}
		/* Subscribe the locator to the manager if hasn't already done that.
		Otherwise does nothing. */
		void subscribe(locator_ptr_t locator) {
			auto& key = typeid(*locator);
			if (locators.contains(key)) return;
			locators[key] = std::move(locator);
		}
		/* Unsubscribe the locator of the given type and return it.
		If the locator wasn't subscribed, returns a nullptr. */
		locator_ptr_t unsubscribe(std::type_index type) {
			if (!locators.contains(type)) return nullptr;
			locator_ptr_t locator = std::move(locators[type]);
			locators.erase(type);
			return locator;
		}
	private:
		/* A mapping from polymorphic component locator types to the locators themselves. */
		std::unordered_map<std::type_index, locator_ptr_t> locators;
	};
}