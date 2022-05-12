# GameObjects

Gameobjects (or `GameObjects`) are the most basic
objects in the scene. That is, every user-defined
object to be present in the scene must inherit
from the gameobject's class (or actually its
interface, more on that later) and be registered
via `SceneManager` singleton.

## Interface (`GameObjectI`)

GameObject Interface (`GameObjectI`) is the very
class that your object must inherit from. It contains the following members:
- `Transform` component,
- a vector of `Mesh` instances,
both of which are public.

The interface also contains the following methods:
- constructors,
- `render(Shader&)` (already defined),
- `update(float delta_time)` (virtual).

### Constructors

Available constructors are:
- `GameObjectI()` (creates empty gameobject),
- `GameObjectI(DefaultMesh, float width, float height)` (creates a gameobject with one of the default meshes and additional parameters if required),
- `GameObjectI(float radius, int seg_num)` (creates a circle gameobject).

All constructors register the gameobject by default.

## Basic instance (`GameObject`)

A simple `GameObject` class is also available for use if you don't need to add custom behaviour
to the object.