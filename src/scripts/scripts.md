# Scripts

The whole point of this engine is for the you to be able to write your own applications using the tools provided. This, at a basic level, means creating custom components and the starting stage of the scene.

All code should be placed in the `src/scripts` folder. There are two approaches in which the code can be organised.

### One project approach
If your goal is to have just one project, all you need to do, is modify the `src/scripts/CMakeLists.txt` file like this:
```CMake
set(SCRIPTS_SOURCE
	# <- your source and header files go here, e.g.:
	# ${CMAKE_CURRENT_SOURCE_DIR}/initialisation.cpp

	PARENT_SCOPE
)
```
> Obviously, the `CMakeLists.txt` file can be extended, however, the important thing is to add all your source and header files to the `SCRIPTS_SOURCE` variable and make that variable visible in `PARENT_SCOPE`.

### Multiple projects approach
If you plan on having multiple projects with an easy way of changing the currently compiled one, you can place the projects in their own folders, create a `CMakeLists.txt` file for each one like above, and create another `CMakeLists.txt` file right in the `src/scripts` directory, containing the following code:
```CMake
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/current_project_folder)

set(SCRIPTS_SOURCE
	${SCRIPTS_SOURCE}
	PARENT_SCOPE
)
```
> This approach is used in the engine's source code. That way, you can easily move between example projects.

## Initialisation

In order to define the starting stage of the scene, the `void SceneManager::instantiate_custom_objects()` method must be implemented.

> Remember to instantiate your objects on the heap (e.g. using the `new` keyword), so that they don't get destroyed when the instantiation method ends. For more practical example, see the Examples section.

## Includes

To make use of the variety of tools the engine provides, specific header files have to be included in your script. Conveniently, the headers are named the same way as the classes they contain, but if you're unsure which to include, take a look directly to the engine's source code.

Also, a handy include bundle for general component implementations is provided and can be included as the "component_utils.hpp" file. 

## Examples

In the `src/scripts/` folder you'll find some example scenes which can help you get around and see how to write your own code in this engine in a more hands-on experience. Each folder named contains the project-specific file, so if you want to build any of the example scenes:
- modify the `add_subdirectory()` line in `src/scripts/CMakeLists.txt` to add the correct project's directory,
- build the whole project.

Curently there are two major example scenes:
- [*Shoot the triangle*](../scripts//v1.1-example-01/example.md) (simple),
- [*Sheep herder*](../scripts/v1.1-example-02/example.md) (a bit more advanced),

each of them having their own markdown overview file (however the technical details are in the commented code itself).

Additionally, minor examples representing individual engine's features are available:
- `v1.2-event-example-01` (`Event` class functionality),
- `v1.2-z_index-example-01` (z-indexing and render layer functionality).