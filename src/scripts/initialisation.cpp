#include "scene.hpp"
#include "scripts/script1.hpp"
#include "scripts/script2.hpp"
#include "scripts/script3.hpp"

// TODO: rewrite to use official registration method from the Scene class
void Scene::instantiate_custom_objects() {
	register_gameobject(new GameObject(DefaultMesh::Blob));
	register_gameobject(new GameObject(DefaultMesh::Rect, 0.3f, 0.2f));
	
	gameobjects[0]->transform.position = {-0.5, 0.4, 0.0f};
	gameobjects[1]->transform.position = {0.0f, 0.0f, 0.0f};

	SomeManager* manager = new SomeManager();
	register_gameobject(manager);
	register_gameobject(new MyObj(manager));
	
	register_gameobject(new Circle(0.3f));

	
}