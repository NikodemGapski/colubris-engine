#pragma once
#include "gameobject.hpp"

template<typename T>
T* GameObject::get_component() {
	return static_cast<T*>(components.at(std::type_index(typeid(T))));
}

template<typename T>
void GameObject::add_component(ComponentI* component) {
	components[std::type_index(typeid(T))] = component;
}

template<typename T>
bool GameObject::has_component() {
	return (components.find(std::type_index(typeid(T))) != components.end());
}