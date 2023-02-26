#include "random.hpp"

Random::Random() : seed(1), cur_value(1) {}
Random::Random(uint seed) : seed(seed), cur_value(seed) {}

int Random::rand(int min, int max) {
	generate_next();
	return min + (cur_value % (max - min + 1));
}
float Random::rand(float min, float max) {
	generate_next();
	return min + (float)cur_value / (float)(mod / (max - min));
}

void Random::generate_next() {
	ll next = ((ll)a * (ll)cur_value + (ll)c) % (ll)mod;
	cur_value = (int)next;
}