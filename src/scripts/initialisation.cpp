#include "scene_manager.hpp"
#include "user_input_example.hpp"
#include "on_collision_example.hpp"
#include "collider.hpp"
#include "text.hpp"
#include <vector>

void SceneManager::instantiate_custom_objects() {
	GameObject* a = new GameObject(DefaultMesh::Blob, {}, {}, {}, NULL);
	
	a->get_component<Transform>()->position = {200.0f, 550.0f};
	
	GameObject* obj1 = new GameObject(DefaultMesh::Circle, {100.0f}, {}, {{0.3f, 0.6f, 0.8f}}, NULL);
	obj1->add_component<CircleScript>(new CircleScript(obj1, 100.0f));

	GameObject* obj12 = new GameObject(DefaultMesh::Rect, {20.0f, 40.0f}, {}, {{0.7f, 0.3f, 0.6f}}, obj1, "world", -1.0f);

	GameObject* obj2 = new GameObject(DefaultMesh::Rect, {100.0f, 100.0f}, {}, {}, NULL);
	obj2->get_component<Transform>()->position = {400.0f, 400.0f};
	obj2->add_component<Collider>(new Collider(obj2,
				{
					ColliderShape(obj2->get_component<Transform>(), {{-50.0f, -50.0f}, {-50.0f, 50.0f}, {50.0f, 50.0f}, {50.0f, -50.0f}})
				}
	));
	obj2->add_component<CollisionComponent>(new CollisionComponent(obj2));

	GameObject* obj3 = new GameObject(DefaultMesh::Rect, {100.0f, 100.0f}, {}, {}, obj2);
	obj3->get_component<Transform>()->position = {70.0f, 70.0f};
	obj3->add_component<Collider>(new Collider(obj3,
				{
					ColliderShape(obj3->get_component<Transform>(), {{-50.0f, -50.0f}, {-50.0f, 50.0f}, {50.0f, 50.0f}, {50.0f, -50.0f}})
				}
	));
	obj3->add_component<CollisionComponent>(new CollisionComponent(obj3));
	obj3->get_component<Transform>()->scale = {0.8f, 0.8f};

	GameObject* obj25 = new GameObject(DefaultMesh::Circle, {10.0f}, {}, {{0.2f, 0.8f, 0.3f}}, obj3);
	obj25->get_component<Transform>()->position = {-100.0f, 0.0f};

	GameObject* obj4 = new GameObject("Text", NULL, "UI");
	obj4->add_component<Text>(new Text(obj4, "Colubris Engine goes brrr", {0.2f, 0.7f, 0.4f}));
	obj4->get_component<Transform>()->position = {50.0f, 700.0f};
}