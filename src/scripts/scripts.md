# Scripts

The whole point of this engine is for the you to be able to write your own applications using the tools provided. This, at a basic level, means creating custom components and the starting stage of the scene.

All code should be placed in the `src/scripts` folder and, for each file added, an entry in the `src/scripts/CMakeLists.txt` should be created.

## Initialisation

In order to define the starting stage of the scene, the `void SceneManager::instantiate_custom_objects()` method must be implemented. It is preferable to put the implementation in the existing `src/scripts/initialisation.cpp` file, but a different name can be chosen granted the modification of the corresponding `CMakeLists.txt` entry.

> Remember to instantiate your objects on the heap (e.g. using the `new` keyword), so that they don't get destroyed when the instantiation method ends. For more practical example, see the Examples section.

## CMakeLists

For CMake to know it needs to compile your files, their corresponding entries must be placed in the `set()` procedure of the `src/scripts/CMakeLists.txt` file. The entry should be defined in the following manner:
- `${CMAKE_CURRENT_SOURCE_DIR}/your_file_location`

where `your_file_location` is your file's relative directory from the `src/scripts/` folder.

## Includes

To make use of the variety of tools the engine provides, specific header files have to be included in your script. Conveniently, the headers are named the same way as the classes they contain, but if you're unsure which to include, take a look directly to the engine's source code.

Also, a handy include bundle for general component implementations is provided and can be included as the "component_utils.hpp" file. 

## Examples

In the `src/scripts/` folder you'll find some example scenes which can help you get around and see how to write your own code in this engine in a more hands-on experience. Each folder named 'v[version no.]-example-[example no.]' contains files which should normally be placed right inside the `src/scripts/` directory, so if you want to build any of the example scenes:
- remove all the files (maybe except for the examples) from the `src/scripts` directory,
- move all the files from the desired example folder to `src/scripts`,
- build the whole project.

Curently there are two example scenes: [*Shoot the triangle*](../scripts//v1.1-example-01/example.md) (simple) and [*Sheep herder*](../scripts/v1.1-example-02/example.md) (a bit more advanced), each of them having their own markdown overview file (however the technical details are in the commented code itself).