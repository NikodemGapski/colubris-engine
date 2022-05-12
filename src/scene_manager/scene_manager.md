# Scene manager

`SceneManager` is a singleton that keeps pointers all the scenes in the project
as well as the id of the currently active scene (can only be one at a time).

The class' main purpose is to make it easy to call methods of the scene
that its object is a part of.

In order for an object (GameObject / Collider) to exist in a scene, it must be registered
by the appropriate method.

## Functionality

Available methods are:
- `start()` (basic setup, meant to be used once, before the first application cycle),
- `update()` (calls `update(float delta_time)` method of the currently active scene, and recalculates time variables),
- `render_current()` (calls `render()` method of the currently active scene),
- `int add_scene(Scene* scene)` (adds the specified scene to the available scenes, runs its `start` method and returns its id),
- `bool set_current(int scene_id)` (sets the scene with the given `scene_id` as the current one; returns false if no such scene exists),
- `Scene* get_current()` (returns a pointer to the current scene; to be used mainly by the scene's objects),
- `float get_time()` (returns time that passed from the application start till the last `update()` method was called),
- `float get_delta_time()` (returns time that has passed between the last two `update()` methods),
- `register_gameobject(GameObjectI* obj)` (registers the given gameobject to the current scene),
- `register_circle_collider(CircleCollider* col)` (registers the given circle collider to the current scene).