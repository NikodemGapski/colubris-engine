# Random

Random is a multiplicative LCG for basic psuedo-random generation.

## Public methods
The class offers the following public methods
- `Random()` (a new generator with a seed of `1`),
- `Random(uint seed)` (a new generator with a given seed; beware not to use `0`, since the generator is multiplicative),
- `int rand(int min, int max)` (generate an integer in range [`min`, `max`]),
- `float rand(float min, float max)` (generate a float in range [`min`, `max`]).
- `uint get_seed()` (returns the generator's initial seed value).

## Generator values

The generator uses the following values:
- `mod = 268435399`,
- `a = 31792125`,
- `c = 0` (since it is a multiplicative one).

The values come from the paper under the following [link](https://www.researchgate.net/publication/220577404_Tables_of_linear_congruential_generators_of_different_sizes_and_good_lattice_structure).

## Advantages over STL

Each generator is an instance of a class, so (unlike with the STL rand()) we can have multiple generators with different seeds working at the same time.