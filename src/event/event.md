# Event system

The engine implements a general event system for emitting and listening to events.

## Event emission

To emit an event with a specified name and some additional data, you must call the templated static method:
```c++
Event::emit(std::string name, T data);
```
where `data` is the event's data of type `T` (any type), or simply:
```c++
Event::emit(std::string name);
```
if the event carries no data.

> An important thing to note here, is that, during the `emit` method, a dynamically allocated copy of the `data` variable is created using the class' copy constructor, which gets deleted after the event is processed.

## Event listening

You can assign a callback function to listen for an event with a specified name, by calling the static method:
```c++
Event::listen(std::string name, std::function<void(Event*)> callback);
```
> Note that as normal functions have a default conversion to `std::function`, that is not the case with methods. If you want to pass a method as a callback listener, use lambda functions:
>```c++
> Event::listen("your event name", [this](Event* event) {
> 		this->your_callback(event);
> });
>```
> in another method of the callback's class.

## `Event` members

The `Event` class has the following non-static member methods:
- `std::string get_name() const` (returns the event's name),
- `T get_data<T>() const` (returns the event's data casted to the `T` type and dereferenced; if the event has no data, throws an exception),
- `bool has_data() const` (checks if the event has any data).

## Event handling
> Disclaimer: this chapter describes the engine's implementation details and no actual functionality.

Event system lifecycle is the following:
- every time an event is emitted, it is added to the event queue of all events with the same name,
- every time a callback listener is added, it is added to the list of listeners in the event queue of all events with the same name,
- once every game cycle all events in every event queue are processed (by calling all the listening callback functions) and deleted (listeners remain).

> Note that given that there are separate queues for each event name, the order of events may not be exactly the same as the actual one if some events are emitted in the same game cycle. Every queue is processed individually as a whole.

> To see when in the game cycle events are processed, see the [`SceneManager`](../scene_manager/scene_manager.md) documentation.