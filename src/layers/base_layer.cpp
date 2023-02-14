#include "base_layer.hpp"

ll BaseLayer::id_counter = 0;

BaseLayer::BaseLayer(std::string name) : id(id_counter++), name(name), active(true) {}

ll BaseLayer::get_id() const {
	return id;
}
bool BaseLayer::is_active() const {
	return active;
}
void BaseLayer::set_active(bool active) {
	this->active = active;
}
std::string BaseLayer::get_name() const {
	return name;
}
