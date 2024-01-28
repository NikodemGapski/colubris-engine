#pragma once

#include "component_locator_i.hpp"
#include "component_locator_worker.hpp"
#include "entity.hpp"
#include "raw_buffer.hpp"

#include <unordered_map>
#include <vector>
#include <algorithm> // std::swap
#include <memory>
#include <ranges>

namespace colubris {

	namespace detail {
		template <std::ranges::range R>
		auto to_vector(R&& r) {
			auto parsable = r | std::views::common;
			return std::vector(parsable.begin(), parsable.end());
		}
	}

	template <class T>
	class ComponentLocator : public ComponentLocatorI {
		using worker_ptr_t = std::unique_ptr<ComponentLocatorWorker<T>>;
	public:
		ComponentLocator() : active_count(0) {}
		/* Create a component locator with a custom worker. */
		ComponentLocator(worker_ptr_t worker) : active_count(0), worker(std::move(worker)) {}
		/* Start components method. */
		virtual void start() {
			// TODO
			throw std::runtime_error("Not implemented!");
		}
		/* Update components method. */
		virtual void update(double dt) {
			worker->update(detail::to_vector(buffer | std::views::take(active_count)), dt);
		}
		virtual ~ComponentLocator() = default;

		/* Check if the entity has the component. */
		bool has(Entity e) const {
			return index.contains(e);
		}
		/* Get a reference to the entity's component.
		Throws std::out_of_range if no such component exists. */
		T& get(Entity e) const {
			return *buffer[index.at(e)];
		}

		/* Create a new active component for the entity if one doesn't already
		exist. Otherwise does nothing. */
		template <class... Args>
		void add(Entity e, Args&&... args) {
			if (has(e)) return;

			T* slot = push();
			if (has_inactive()) {
				// Move the first inactive component to the back.
				move(active_count, buffer.size() - 1);
				slot = buffer[active_count];
			}
			*slot = T(std::forward<Args>(args)...);

			entity[active_count] = e;
			index[e] = active_count++;
		}

		/* Remove the entity's component if it exists. Otherwise does nothing. */
		void remove(Entity e) {
			if (!has(e)) return;

			// Properly empty the idx slot if needed.
			size_t idx = index.at(e);
			bool was_active = is_active(idx);
			size_t replacement = find_replacement(idx);
			move(replacement, idx);
			// Properly empty the replacement slot if needed.
			move(find_replacement(replacement), replacement);

			index.erase(e);
			if (was_active)
				--active_count;
			pop();
		}

		/* Set the entity's component activation status to state if it exists.
		Otherwise does nothing. */
		void set_active(Entity e, bool state) {
			if (!has(e)) return;
			size_t idx = index.at(e);
			// The component is already in the desired state.
			if (is_active(idx) == state) return;
			if (is_active(idx)) {
				swap(idx, find_replacement(idx));
				--active_count;
			} else {
				swap(idx, active_count);
				++active_count;
			}
		}

		/* A persistent iterator for a given entity. Remains valid even
		after internal component reorganisation. */
		class handle {
		public:
			handle(Entity e) : e(e) {}
			T& operator*() const {
				return get(e);
			}
		private:
			const Entity e;
		};

		/* Get a handle to the entity's component. */
		handle find(Entity e) const {
			return handle(e);
		}
	private:
		/* A mappnig from entities to their components' indices in the buffer. */
		std::unordered_map<Entity, size_t> index;
		/* The component buffer. */
		RawBuffer<T> buffer;
		/* A mapping from buffer indices to entities. */
		std::vector<Entity> entity;
		/* The number of active components. */
		size_t active_count;
		/* The worker responsible for executing game loop methods. */
		worker_ptr_t worker;

		/* Check if the component at the given index is active. */
		bool is_active(size_t idx) const {
			return idx < active_count;
		}
		/* Check if there are any inactive components. */
		bool has_inactive() const {
			return active_count < buffer.size();
		}
		/* Find a replacement index for the component at the specified index,
		assuming the specified index is to be emptied. Return idx if no such
		index exists. */
		size_t find_replacement(size_t idx) {
			return is_active(idx) ? active_count - 1 : buffer.size() - 1;
		}
		/* Push the buffer and update entity mapping. */
		T* push() {
			T* res = buffer.push();
			entity.push_back(0);
			return res;
		}
		/* Pop the buffer and update entity mappping. */
		void pop() {
			buffer.pop();
			entity.pop_back();
		}
		/* Move the component at src index to dest index in the buffer. */
		void move(size_t src, size_t dest) {
			if (src == dest) return;
			buffer.move(src, dest);
			index[entity[src]] = dest;
			entity[dest] = entity[src];
		}
		/* Swap the components at a and b buffer indices. */
		void swap(size_t a, size_t b) {
			if (a == b) return;
			buffer.swap(a, b);
			std::swap(index[entity[a]], index[entity[b]]);
			std::swap(entity[a], entity[b]);
		}
	};
}