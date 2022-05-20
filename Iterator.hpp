#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft {

template <class Iterator>
class iterator_traits {
	public:
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
};

template <class T>
class iterator_traits<T*> {
	public:
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
};

template <class T>
class iterator_traits<const T*> {
	public:
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef random_access_iterator_tag	iterator_category;
};

template <class Category, class T, class Distance = std::ptrdiff_t,
          class Pointer = T*, class Reference = T&>
struct base_iterator {
	public:
		typedef T         		value_type;
		typedef Distance  		difference_type;
		typedef Pointer   		pointer;
		typedef const Pointer	const_pointer;
		typedef Reference 		reference;
		typedef const Reference const_reference;
		typedef Category  		iterator_category;
};

struct random_access_iterator_tag {};

template <typename T>
class ra_iterator : public base_iterator<random_access_iterator_tag, T> {
	typedef base_iterator<random_access_iterator_tag, T> base;

	private:
		typename base::pointer _pointer;

	public:
		ra_iterator(): _pointer(nullptr) {}
		ra_iterator(typename base::pointer pointer): _pointer(pointer) {}
		ra_iterator(const ra_iterator& other): _pointer(other._pointer) {}
		virtual ~ra_iterator() {}

		ra_iterator&	operator=(ra_iterator const &other) {
			this->_pointer = other._pointer;
		}

		typename base::reference operator*() {
			return (*this->_pointer);
		}
		typename base::const_reference operator*() const {
			return (*this->_pointer);
		}
		typename base::pointer operator->() {
			return (this->_pointer);
		}
		typename base::const_pointer operator->() const {
			return (this->_pointer);
		}
		typename base::reference operator[](int value) {
			return (*(this->_pointer + value));
		}
		typename base::const_reference operator[](int value) const {
			return (*(this->_pointer + value));
		}

		ra_iterator operator++(int){
			ra_iterator	temp(*this);
			this->_pointer++;
			return (temp);
		}
		ra_iterator operator++() {
			this->_pointer++;
			return (*this);
		}
		ra_iterator operator--(int){
			ra_iterator	temp(*this);
			this->_pointer--;
			return (temp);
		}
		ra_iterator operator--() {
			this->_pointer--;
			return (*this);
		}

		ra_iterator &operator+=(int value) {
			this->_pointer += value;
			return (*this);
		}
		ra_iterator &operator+(int value) const {
			ra_iterator temp(*this);
			return (temp += value);
		}
		ra_iterator &operator-=(int value) {
			this->_pointer -= value;
			return (*this);
		}
		ra_iterator &operator-(int value) const {
			ra_iterator temp(*this);
			return (temp -= value);
		}
		typename base::difference_type operator-(const ra_iterator& other) const {
			return (this->_pointer - other._pointer);
		} 

		#define op(o) bool operator o (ra_iterator const &other) const { return (this->_pointer o other._pointer); }
			op(<)
			op(>)
			op(<=)
			op(>=)
			op(==)
			op(!=)
		#undef op
};

template <typename T>
class reverse_iterator : public base_iterator<random_access_iterator_tag, T> {
	typedef base_iterator<random_access_iterator_tag, T> base;

	private:
		typename base::pointer _pointer;

	public:
		reverse_iterator(): _pointer(nullptr) {}
		reverse_iterator(typename base::pointer pointer): _pointer(pointer) {}
		reverse_iterator(const reverse_iterator& other): _pointer(other._pointer) {}
		virtual ~reverse_iterator() {}

		reverse_iterator&	operator=(reverse_iterator const &other) {
			this->_pointer = other._pointer;
			return (*this);
		}

		typename base::reference operator*() {
			return (*this->_pointer);
		}
		typename base::const_reference operator*() const {
			return (*this->_pointer);
		}
		typename base::pointer operator->() {
			return (this->_pointer);
		}
		typename base::const_pointer operator->() const {
			return (this->_pointer);
		}
		typename base::reference operator[](int value) {
			return (*(this->_pointer + value));
		}
		typename base::const_reference operator[](int value) const {
			return (*(this->_pointer + value));
		}

		reverse_iterator operator++(int){
			reverse_iterator	temp(*this);
			this->_pointer--;
			return (temp);
		}
		reverse_iterator operator++() {
			this->_pointer--;
			return (*this);
		}
		reverse_iterator operator--(int){
			reverse_iterator	temp(*this);
			this->_pointer++;
			return (temp);
		}
		reverse_iterator operator--() {
			this->_pointer++;
			return (*this);
		}

		reverse_iterator &operator+=(int value) {
			this->_pointer -= value;
			return (*this);
		}
		reverse_iterator &operator+(int value) const {
			reverse_iterator temp(*this);
			return (temp -= value);
		}
		reverse_iterator &operator-=(int value) {
			this->_pointer += value;
			return (*this);
		}
		reverse_iterator &operator-(int value) const {
			reverse_iterator temp(*this);
			return (temp += value);
		}
		typename base::difference_type operator-(const reverse_iterator& other) const {
			return (other._pointer - this->_pointer);
		} 

		#define op(o) bool operator o (reverse_iterator const &other) const { return (other._pointer o this->_pointer); }
			op(<)
			op(>)
			op(<=)
			op(>=)
			op(==)
			op(!=)
		#undef op
};

}

#endif