#pragma once

class ComponentLocatorI {
public:
	virtual void start() = 0;
	virtual void update(double dt) = 0;
	virtual ~ComponentLocatorI() = default;
};