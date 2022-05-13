#include "scene.hpp"
#include "scripts/script1.hpp"
#include "scripts/script2.hpp"
#include "scripts/script3.hpp"

void Scene::instantiate_custom_objects() {
	register_gameobject(new GameObject(DefaultMesh::Blob));
	register_gameobject(new GameObject(DefaultMesh::Rect, 0.3f, 0.2f));
	
	gameobjects[0]->get_component<Transform>()->position = {-0.5, 0.4, 0.0f};
	gameobjects[1]->get_component<Transform>()->position = {0.0f, 0.0f, 0.0f};

	// SomeManager* manager = new SomeManager();
	// register_gameobject(manager);
	// register_gameobject(new MyObj(manager));
	
	GameObject* obj1 = new GameObject(0.3f);
	obj1->add_component<CircleScript>(new CircleScript(obj1, 0.3f));
	register_gameobject(obj1);

	
}