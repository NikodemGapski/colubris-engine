#include "scene_manager.hpp"
#include "scripts/script1.hpp"
#include "scripts/script2.hpp"
#include "scripts/script3.hpp"
#include "collider/collider.hpp"
#include <vector>

void SceneManager::instantiate_custom_objects() {
	register_gameobject(new GameObject(DefaultMesh::Blob));
	
	gameobjects[0]->get_component<Transform>()->position = {-0.5, 0.4, 0.0f};

	// SomeManager* manager = new SomeManager();
	// register_gameobject(manager);
	// register_gameobject(new MyObj(manager));
	
	GameObject* obj1 = new GameObject(0.3f);
	obj1->add_component<CircleScript>(new CircleScript(obj1, 0.3f));
	register_gameobject(obj1);

	GameObject* obj2 = new GameObject(DefaultMesh::Rect, 0.2f, 0.2f);
	obj2->add_component<Collider>(new Collider(obj2,
				{
					ColliderShape({{-0.1f, -0.1f}, {-0.1f, 0.1f}, {0.1f, 0.1f}, {0.1f, -0.1f}})
				}
	));
	register_gameobject(obj2);

	GameObject* obj3 = new GameObject(DefaultMesh::Rect, 0.2f, 0.2f);
	obj3->get_component<Transform>()->position = {-0.25f, 0.0f, 0.0f};
	obj3->add_component<Collider>(new Collider(obj3,
				{
					ColliderShape({{-0.1f, -0.1f}, {-0.1f, 0.1f}, {0.1f, 0.1f}, {0.1f, -0.1f}})
				}
	));
	register_gameobject(obj3);
}