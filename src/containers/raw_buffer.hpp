#pragma once

#include <cstddef> // size_t, std::ptrdiff_t
#include <cstring> // std::memcpy
#include <cstdlib> // std::malloc, std::free

namespace colubris {

	/* A contingous buffer for storing elements of the same type. */
	template <class T>
	class RawBuffer {
	public:
		constexpr static size_t START_CAPACITY = 16;
		constexpr static double INCREASE_FACTOR = 1.6;
		constexpr static double DECREASE_FACTOR = 1.0 / 1.6;
		constexpr static double LOW_FACTOR = DECREASE_FACTOR * DECREASE_FACTOR;

		RawBuffer() : size_value(0), capacity(START_CAPACITY) {
			start = (T*)std::malloc(sizeof(T) * capacity);
		}
		~RawBuffer() {
			std::free(start);
		}

		/* Get a pointer to the index slot in the buffer. */
		T* operator[](size_t index) const {
			return start + index;
		}
		/* Move the contents of the src slot to the dest slot. If src == dest, does nothing. */
		void move(size_t src, size_t dest) {
			if (src == dest) return;
			std::memcpy(operator[](dest), operator[](src), sizeof(T));
		}
		/* Swap the contents of the a and b slots. If a == b, does nothing. */
		void swap(size_t a, size_t b) {
			if (a == b) return;
			// Make a copy of b's contents.
			T* tmp = (T*)std::malloc(sizeof(T));
			std::memcpy(tmp, operator[](b), sizeof(T));
			// Move a to b.
			move(a, b);
			// Copy the b's contents back to the buffer.
			std::memcpy(operator[](a), tmp, sizeof(T));
			std::free(tmp);
		}
		/* Increase the buffer size and return the pointer to the new slot. */
		T* push() {
			if (size() + 1 > capacity)
				increase_capacity();
			return start + (size_value++);
		}
		/* Decrease the buffer size. */
		void pop() {
			if (size() - 1 < (double)capacity * LOW_FACTOR)
				decrease_capacity();
			--size_value;
		}
		/* Get the buffer size. */
		size_t size() const {
			return size_value;
		}

		class iterator {
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = T*;
			using difference_type = std::ptrdiff_t;
			iterator() : ptr(nullptr) {}
			iterator& operator++() {
				++ptr;
				return *this;
			}
			iterator operator++(int) {
				iterator res(*this);
				operator++();
				return res;
			}
			bool operator==(const iterator& other) const {
				return ptr == other.ptr;
			}
			bool operator!=(const iterator& other) const {
				return !operator==(other);
			}
			T* operator*() const {
				return ptr;
			}
		private:
			iterator(T* ptr) : ptr(ptr) {}
			T* ptr;

			friend iterator RawBuffer::begin() const;
			friend iterator RawBuffer::end() const;
		};

		iterator begin() const {
			return iterator(start);
		}
		iterator end() const {
			return iterator(start + size());
		}
	private:
		T* start;
		size_t size_value;
		size_t capacity;

		void change_capacity(size_t new_capacity) {
			T* tmp = (T*)std::malloc(sizeof(T) * new_capacity); // Potential throw. No leaks.
			std::memcpy(tmp, start, capacity);
			free(start);
			start = tmp;
			capacity = new_capacity;
		}
		void increase_capacity() {
			change_capacity((double)capacity * INCREASE_FACTOR);
		}
		void decrease_capacity() {
			change_capacity((double)capacity * DECREASE_FACTOR);
		}
	};
}