# Math

`math` is a utility namespace for mathematical operations.

## Available functions

There are the following available functions:
- `Type min(Type, Type)`,

- `Type max(Type, Type)`,

- `void swap(Type&, Type&)`,

- `bool is_inf(float)`,

- `bool belongs_to(float c, float a, float b)` (whether `c` belongs to range `<min(a,b),max(a,b)>`,

- `bool ranges_intersect(float a, float b, float c, float d)` (whether ranges `<min(a,b),max(a,b)>` and `<min(c,d),max(c,d)>` intersect),

- `float cross(glm::vec2 v, glm::vec2 w)` (signed area of the triangle based on v and w (the same sign as sin(angle(v, w))))

- `bool are_parallel(glm::vec2, glm::vec2)` (whether two vectors are parallel)

- `glm::vec2 intersection(Line a, Line b)` (intersection point between two non-parallel lines (throws division by 0 exception when parallel))

- `bool segments_intersect(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2)` (whether two segments intersect)

- `void add_collision_points(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2, std::vector<glm::vec2>& result)` (add collision points of segments a and b to the result vector (or none if there is no collision))

And the following structures:
- `Line`:
- - `Line(glm::vec2 a, glm::vec2 b)` (creates a line through points a and b),
- - `float A, B, C` (directional coefficients of the line satisfying the line equation: `Ax + By + C = 0`),

... and constants:
- `float INF` (infinity, equal to the value of the `HUGE_VAL` macro).