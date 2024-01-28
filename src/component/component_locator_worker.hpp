#pragma once
#include <concepts> // std::same_as
#include <vector>

namespace colubris {

	namespace detail {
		template <class C>
		concept has_start = requires(C c) {
			{ c.start() } -> std::same_as<void>;
		};
		template <class C>
		concept has_update = requires(C c) {
			{ c.update(1.0) } -> std::same_as<void>;
		};
	}

	template <class T>
	class ComponentLocatorWorker {
	public:
		/* Start components method (customizable if needed). */
		virtual void start(std::vector<T*>&& components) {
			if constexpr (detail::has_start<T>) {
				for (T* component : components)
					component->start();
			}
		}
		/* Update components method (customizable if needed). */
		virtual void update(std::vector<T*>&& components, double dt) {
			if constexpr (detail::has_update<T>) {
				for (T* component : components)
					component->update(dt);
			}
		}
	};
}