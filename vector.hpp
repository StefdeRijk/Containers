#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "Iterator.hpp"
#include "Compare.hpp"

namespace ft {
	template < class T, class Alloc = std::allocator<T> >

	class vector
	{
		public:
			typedef T							value_type;
			typedef	Alloc						allocator_type;
			typedef value_type&					reference;
			typedef const value_type&			const_reference;
			typedef value_type*					pointer;
			typedef const value_type*			const_pointer;
			typedef size_t						size_type;
			typedef ra_iterator<T>				iterator;
			typedef const iterator				const_iterator;
			typedef reverse_iterator<T>			reversed_iterator;
			typedef const reverse_iterator<T>	const_reversed_iterator;
			typedef ptrdiff_t					difference_type;
		private:
			allocator_type	_alloc;
			size_type		_size;
			size_type		_cap;
			T*				_data;

		public:

			explicit vector(const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _cap(0), _data(0) {};
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
				_alloc(alloc), _size(n), _cap(n), _data(_alloc.allocate(n)) {
					for (size_type i = 0; i < _size; i++)
						this->_data[i] = val;
				}
			vector (ra_iterator<T> first, ra_iterator<T> last, const allocator_type& alloc = allocator_type()):
				_alloc(alloc), _size(last - first), _cap(_size) {
					if (first < last)
						this->_data = this->_alloc.allocate(_cap);
					else if (first == last) {
						this->_data = NULL;
						return;
					}
					else {
						this->_size = 0;
						this->_cap = 0;
						this->_data = NULL;
						throw std::length_error("vector");
					}
					for (size_type i = 0; first < last; first++) {
						this->_data[i++] = *first;
					}
				}
			vector (const vector& x): _alloc(x._alloc), _size(x._size), _cap(x._cap), _data(_alloc.allocate(_cap)) {
				for (size_type i = 0; i < _size; i++) {
					this->_data[i] = x._data[i];
				}
			}

			~vector () {
				this->clear();
				if (this->_data)
					delete(this->_data);
			}

			vector& operator=(const vector& x) {
				this->~vector<T>();
				this->_size = x._size;
				this->_cap = x._cap;
				if (this->_cap)
					this->_data = this->_alloc.allocate(_cap);
				for (size_type i = 0; i < this->_size; i++) {
					this->_data[i] = x._data[i];
				}
				return (*this);
			}

			iterator begin() {return iterator(this->_data);}
			const_iterator begin() const {return iterator(this->_data);}
			iterator end() {return iterator(&this->_data[this->_size]);}
			const_iterator end() const {return iterator(&this->_data[this->_size]);}
			reversed_iterator rbegin() {return reversed_iterator(&this->_data[this->_size - 1]);}
			const_reversed_iterator rbegin() const {return reversed_iterator(&this->_data[this->_size - 1]);}
			reversed_iterator rend() {return reversed_iterator(this->_data - 1);}
			const_reversed_iterator rend() const {return reversed_iterator(this->_data - 1);}

			size_type size() const {return this->_size;}
			size_type max_size() const {return std::numeric_limits<size_type>::max() / sizeof(T);}
			void resize (size_type n, value_type val = value_type()) {
				if (n < this->_size) {
					for (size_type i = n; i < this->_size; i++) {
						this->_data[i].~T();
					}
					this->_size = n;
				}
				else {
					reserve(n);
					for (size_type i = n; i < n; i++) {
						this->_data[i] = val;
					}
					this->_size = n;
					this->_cap = n;
				}
			}
			size_type capacity() const {return this->_cap;}
			bool empty() const {return this->_size == 0;}
			void reserve (size_type n) {
				if (!this->_data) {
					this->_cap = n;
					this->_data = this->_alloc.allocate(this->_cap);
					return ;
				}
				if (n > this->max_size())
					throw std::length_error("vector");
				if (n > this->_cap) {
					pointer temp = this->_alloc.allocate(n);
					for (size_type i = 0; i < this->_size; i++) {
						this->_alloc.construct(&temp[i], this->_data[i]);
						this->_data[i].~T();
					}
					this->_alloc.deallocate(this->_data, this->_cap);
					this->_data = temp;
					this->_cap = n;
				}
			}

			reference operator[] (size_type n) {return this->_data[n];}
			const_reference operator[] (size_type n) const {return this->_data[n];}
			reference at (size_type n) {
				if (n < 0 || n > this->_size)
					throw std::out_of_range("vector");
				return this->_data[n];
			}
			const_reference at (size_type n) const {
				if (n < 0 || n > this->_size)
					throw std::out_of_range("vector");
				return this->_data[n];
			}
			reference front() {return this->_data[0];}
			const_reference front() const {return this->_data[0];}
			reference back() {return this->_data[this->_size - 1];}
			const_reference back() const {return this->_data[this->_size - 1];}

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last) {
				if (first < last)
					throw std::length_error("vector");
				resize(first - last);
				for (size_type i = 0; first < last; first++) {
					this->_data[i++] = *first;
				}
			}
			void assign (size_type n, const value_type& val) {
				resize(n);
				for (size_type i = 0; i < n; i++) {
					this->_data[i] = val;
				}
			}
			void push_back (const value_type& val) {
				if (this->_cap == this->_size) {
					if (this->_cap * 2 <= max_size())
						reserve(this->_cap * 2);
					else
						reserve(this->_cap + 1);
				}
				this->_data[this->size] = val;
				this->_size++;
			}
			void pop_back() {
				resize(this->_size - 1);
			}
			iterator insert (iterator position, const value_type& val) {
				iterator	ret_position = position;
				resize(this->_size + 1);
				T temp = val;
				for (; position < end(); position++) {
					T copy = *position;
					*position = temp;
					temp = copy;
				}
				return (ret_position);
			}
			void insert (iterator position, size_type n, const value_type& val) {
				size_type	start = position - begin();
				resize(this->_size + n);
				for (size_type i = this->_size - 1; i >= start + n; i--) {
					this->_data[i] = this->_data[i - n];
				}
				for (size_type i = start; i < start + n; i++) {
					this->_data[i] = val;
				}
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last) {
				size_type	start = position - begin();
				size_type	n = last - first;
				resize(this->_size + n);
				for (size_type i = this->_size - 1; i >= start + n; i--) {
					this->_data[i] = this->_data[i - n];
				}
				for (size_type i = 0; i < n; i++) {
					this->_data[start + i] = *(first + i);
				}
			}
			iterator erase (iterator position) {
				return (erase(position, position + 1));
			}
			iterator erase (iterator first, iterator last) {
				for (;last < end(); last++) {
					_alloc.destroy(&(*first));
					*first = *last;
					first++;
				}
				this->_size -= last - first;
				return (last - 1);
			}
			void swap (vector& x) {
				std::swap(this->_alloc, x._alloc);
				std::swap(this->_size, x._size);
				std::swap(this->_cap, x._cap);
				std::swap(this->_data, x._data);
			}
			void clear() {
				for (size_type i = 0; i < this->_size; i++) {
					this->_data[i].~T();
				}
				this->_size = 0;
			}

			allocator_type get_allocator() const {return this->_alloc;}
	};
}

template <class T, class Alloc>
bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}
template <class T, class Alloc>
bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
	return (!lhs == rhs);
}
template <class T, class Alloc>
bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}
template <class T, class Alloc>
bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
	return (lhs < rhs || lhs == rhs);
}
template <class T, class Alloc>
bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
	return (!lhs <= rhs);
}
template <class T, class Alloc>
bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
	return (lhs > rhs || lhs == rhs);
}

template <class T, class Alloc>
void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y) {
	x.swap(y);
}

#endif