# Scripts

The whole point of this engine is for the developer to be able to write their own applications using the tools provided. This, at a basic level, means creating custom components and the starting stage of the scene.

All code should be placed in the `src/scripts` folder and, for each file added, an entry in the `src/scripts/CMakeLists.txt` should be created.

## Initialisation

In order to define the starting stage of the scene, the `void SceneManager::instantiate_custom_objects()` method must be implemented. It is preferable to put the implementation in the existing `src/scripts/initialisation.cpp` file, but a different name can be chosen granted the modification of the corresponding `CMakeLists.txt` entry.

> Remember to instantiate your objects on the heap (e.g. using the `new` keyword), so that they don't get destroyed when the instantiation method ends.

## CMakeLists

For CMake to know it needs to compile your files, their corresponding entries must be placed in the `set()` procedure of the `src/scripts/CMakeLists.txt` file. The entry should be defined in the following manner:
- `${CMAKE_CURRENT_SOURCE_DIR}/your_file_location`

where `your_file_location` is your file's relative directory from the `src/scripts/` folder.

## Includes

To make use of the variety of tools the engine provides, specific header files have to be included in your script. Conveniently, the headers are named the same way as the classes they contain, but if you're unsure which to include, take a look directly to the engine's source code.

## Examples

In the `src/scripts/` folder you'll find some example scripts which show the use of certain features of the engine.