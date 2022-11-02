#include "scene_manager.hpp"
#include "user_input_example.hpp"
#include "on_collision_example.hpp"
#include "collider.hpp"
#include <vector>

void SceneManager::instantiate_custom_objects() {
	GameObject* a = new GameObject(DefaultMesh::Blob);
	
	a->get_component<Transform>()->position = {-0.5, 0.4, 0.0f};
	
	GameObject* obj1 = new GameObject(0.3f);
	obj1->add_component<CircleScript>(new CircleScript(obj1, 0.3f));

	GameObject* obj2 = new GameObject(DefaultMesh::Rect, 0.2f, 0.2f);
	obj2->add_component<Collider>(new Collider(obj2,
				{
					ColliderShape(obj2->get_component<Transform>(), {{-0.1f, -0.1f}, {-0.1f, 0.1f}, {0.1f, 0.1f}, {0.1f, -0.1f}})
				}
	));
	obj2->add_component<CollisionComponent>(new CollisionComponent(obj2));

	GameObject* obj3 = new GameObject(DefaultMesh::Rect, 0.2f, 0.2f);
	obj3->get_component<Transform>()->position = {-0.25f, 0.0f, 0.0f};
	obj3->add_component<Collider>(new Collider(obj3,
				{
					ColliderShape(obj3->get_component<Transform>(), {{-0.1f, -0.1f}, {-0.1f, 0.1f}, {0.1f, 0.1f}, {0.1f, -0.1f}})
				}
	));
	obj3->add_component<CollisionComponent>(new CollisionComponent(obj3));
}