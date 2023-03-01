#pragma once
#include "component_utils.hpp"
#include "main_layer.hpp"
#include "render_layer.hpp"
#include "layer_collection.hpp"
#include "player_controller.hpp"
#include "renderer.hpp"
#include "game_data.hpp"
#include "collider.hpp"

struct Flower {
	GameObject* obj;
	glm::vec2 pos;
	Flower() : pos(glm::vec2(0.0f)), obj(NULL) {}
	Flower(GameObject* obj, glm::vec2 pos) : pos(pos), obj(obj) {}
};
struct Tile {
	GameObject* obj;
	int i, j;
	// tile type (0 - plains, 1 - forest, 2 - desert)
	Type type;
	Tile() : i(0), j(0), obj(NULL) {}
	Tile(int i, int j, GameObject* obj, Type type) : i(i), j(j), obj(obj), type(type) {}
};
struct Chunk {
	MainLayer* layer;
	Layer* collision_layer;
	Tile tile;
	int i, j;
	std::vector<Flower> flowers;
	Chunk() : i(0), j(0), layer(NULL), collision_layer(NULL) {}
	Chunk(int i, int j) : i(i), j(j), layer(NULL), collision_layer(NULL) {}
};

class GameManager : public ComponentI {
public:
	GameManager(GameObject* parent, GameObject* sheep) : ComponentI(parent), sheep(sheep) {
		collision_collection = LayerCollection::find_collection("Collision");
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				// create a chunk
				MainLayer::add_layer(name(i, j));
				chunks[i][j] = Chunk(i, j);
				chunks[i][j].layer = MainLayer::find_layer(name(i, j));
				chunks[i][j].layer->set_active(false);

				collision_collection->add(name(i, j));
				chunks[i][j].collision_layer = collision_collection->find(name(i, j));
				chunks[i][j].collision_layer->set_active(false);

				// add a tile to the chunk
				create_tile(i, j);
			}
		}
	}

	void start() {}
	void update() {
		// keep the player inside the map
		GameData::player_pos = {
			math::clamp(GameData::player_pos.x, -(n / 2 - 1) * chunk_size, (n / 2 - 2) * chunk_size),
			math::clamp(GameData::player_pos.y, -(n / 2 - 1) * chunk_size, (n / 2 - 2) * chunk_size)
		};

		// update active chunks
		update_activity();
		// update positions in active chunks
		update_pos();
		// update the sheep's chunk
		glm::ivec2 pos = tile_idx(GameData::sheep_pos);
		GameData::sheep_tile_type = chunks[pos.x][pos.y].tile.type;
		MainLayer::find_layer(name(pos.x, pos.y))->add(sheep);
		collision_collection->find(name(pos.x, pos.y))->add(sheep);
	}

	void eat_flower(GameObject* flower) {
		// find the flower's chunk (the same as the sheep)
		glm::ivec2 pos = tile_idx(GameData::sheep_pos);
		auto& chunk = chunks[pos.x][pos.y];
		for(auto i = chunk.flowers.begin(); i != chunk.flowers.end(); ++i) {
			if(i->obj != flower) continue;
			chunk.flowers.erase(i);
			break;
		}
		GameObject::destroy_gameobject(flower);
		GameData::increment_score();
	}

private:
	// number of chunks
	inline static const int n = 50;
	inline static const float chunk_size = 250.0f;
	Chunk chunks[n][n];
	LayerCollection* collision_collection;
	// the player's visibility radius in chunks in Manhattan distance
	static const int visibility_radius = 4;
	std::vector<Chunk> active_chunks;
	// the sheep gameobject
	GameObject* sheep;

	void create_tile(int i, int j) {
		// tile type (0 - plains, 1 - forest, 2 - desert)
		Type tile_type = (Type)GameData::random.rand(0, 2);
		glm::vec3 tile_colour;
		switch (tile_type) {
		case Type::Plains:
			tile_colour = Renderer::rgb_colour(130, 210, 100);
			break;
		case Type::Forest:
			tile_colour = Renderer::rgb_colour(60, 130, 30);
			break;
		default:
			tile_colour = Renderer::rgb_colour(255, 204, 0);
			break;
		}
		chunks[i][j].tile = Tile(i, j, new GameObject("Tile", DefaultMesh::Rect, {chunk_size, chunk_size}, {}, {
			tile_colour
		}, NULL), tile_type);
		RenderLayer::find_layer("background")->add(chunks[i][j].tile.obj);
		chunks[i][j].layer->add(chunks[i][j].tile.obj);

		// add flowers to the chunk
		create_flowers(i, j, tile_type);
	}

	void create_flowers(int i, int j, int tile_type) {
		// no flowers on desert tiles
		if(tile_type == Type::Desert) return;
		int flower_count = 0;
		// some flowers on forest tiles
		if(tile_type == Type::Forest) {
			flower_count = GameData::random.rand(1, 3);
		}
		// a lot of flowers on plains tiles
		if(tile_type == Type::Plains) {
			flower_count = GameData::random.rand(3, 5);
		}
		// create the flowers
		for(int f = 0; f < flower_count; ++f) {
			create_flower(i, j);
		}
	}

	void create_flower(int i, int j) {
		// flower radius
		float radius = GameData::random.rand(8.0f, 12.0f);
		GameObject* flower = new GameObject("Flower", DefaultMesh::Circle, {radius}, {}, {
			Renderer::rgb_colour(255, 0, 0)
		}, NULL, 2.0f);

		// flower position
		glm::vec2 pos = tile_pos(chunks[i][j].tile) + glm::vec2(
			GameData::random.rand(-chunk_size / 2.0f, chunk_size / 2.0f), 
			GameData::random.rand(-chunk_size / 2.0f, chunk_size / 2.0f)
		);
		chunks[i][j].flowers.push_back(Flower(flower, pos));

		// simplified square collider added to the (i, j) chunk
		float a = radius / 1.41f / 2.0f;
		ColliderShape shape(flower->transform, {
			{-a, -a}, {a, -a}, {a, a}, {-a, a}
		});
		flower->add_component<Collider>(new Collider(flower, {shape}));
		collision_collection->find(name(i, j))->add(flower);

		// add the flower to the layer
		chunks[i][j].layer->add(flower);
	}

	// update lists of active chunks and tiles
	void update_activity() {
		glm::ivec2 pos = tile_idx(GameData::player_pos);
		GameData::player_tile_type = chunks[pos.x][pos.y].tile.type;

		for(auto chunk : active_chunks) {
			chunk.layer->set_active(false);
			chunk.collision_layer->set_active(false);
		}
		active_chunks.clear();

		for(int i = -visibility_radius; i <= visibility_radius; ++i) {
			for(int j = -visibility_radius; j <= visibility_radius; ++j) {
				if(math::abs(i) + math::abs(j) > visibility_radius) continue;

				int i_idx = pos.x + i, j_idx = pos.y + j;
				if(i_idx < 0 || i_idx >= n || j_idx < 0 || j_idx >= n) continue;

				chunks[i_idx][j_idx].layer->set_active(true);
				chunks[i_idx][j_idx].collision_layer->set_active(true);
				active_chunks.push_back(chunks[i_idx][j_idx]);
			}
		}
	}

	// update positions of tiles and flowers in active chunks relative to the player
	void update_pos() {
		for(auto chunk : active_chunks) {
			chunk.tile.obj->transform->position = GameData::position(tile_pos(chunk.tile));
			for(auto flower : chunk.flowers) {
				flower.obj->transform->position = GameData::position(flower.pos);
			}
		}
	}

	// transform coordinates into a unique id
	static std::string name(int i, int j) {
		return std::to_string(n * i + j);
	}

	// position of the tile in the world
	static glm::vec2 tile_pos(Tile tile) {
		return glm::vec2(
			chunk_size * (float)(tile.i - n / 2),
			chunk_size * (float)(tile.j - n / 2));
	}

	// which tile the given position belongs to
	static glm::ivec2 tile_idx(glm::vec2 pos) {
		int h_pos = n / 2 + math::floor(pos.x / chunk_size + 0.5f);
		int v_pos = n / 2 + math::floor(pos.y / chunk_size + 0.5f);
		return {h_pos, v_pos};
	}
};