#pragma once
#include <cstdlib>

typedef long long ll;

// Linear multiplicative congruential 'random' number generator
class Random {
public:
	// create a Random generator with the seed value of 1
	Random();
	// create a Random generator with the given seed value
	Random(uint seed);

	// generate a random integer in range [min, max]
	int rand(int min, int max);
	// generate a random float in range [min, max]
	float rand(float min, float max);
	// return the generator's seed value
	uint get_seed() const;

private:
	uint seed;
	uint cur_value;
	// values from:
	// https://www.researchgate.net/publication/220577404_Tables_of_linear_congruential_generators_of_different_sizes_and_good_lattice_structure
	const uint mod = 268435399, a = 31792125, c = 0;

	// evaluate and update the next cur_value
	void generate_next();
};