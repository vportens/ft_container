#ifndef STACK_H
# define STACK_H

#include "vector.hpp"
//#include <stack>

namespace ft {
template <class T, class Container = ft::vector<T> >
class stack {

	public:
	typedef T	value_type;
	typedef size_t	size_type;
	typedef		 Container	container_type;

	protected:
		Container c;
	
	public:
		explicit stack(const Container&cpy = Container()) :c(cpy){};

	bool empty() const {return c.empty();}
	size_type size() const {return c.size();}
	value_type&	top() {return c.back();}
	const value_type& top() const {return c.back();}
	void	push(const value_type &x) {return c.push_back(x);}
	void pop() {c.pop_back();}

	friend bool	operator==(const stack<T, Container> &x, const stack<T, Container> &y){
		return (x.c == y.c);}


	friend bool	operator<(const stack<T, Container> &x, const stack<T, Container> &y)
		{return (x.c < y.c);}
};





template <class T, class Container>
bool	operator>(const stack<T, Container> &x, const stack<T, Container> &y){
	if (x<y || x == y)
		return (false);
	return (true);
}


template <class T, class Container>
bool	operator!=(const stack<T, Container> &x, const stack<T, Container> &y) {
	return (!(x == y));
}


template <class T, class Container>
bool	operator<=(const stack<T, Container> &x, const stack<T, Container> &y) {
	return (!(x > y));
}


template <class T, class Container>
bool	operator>=(const stack<T, Container> &x, const stack<T, Container> &y) {
	return (!(x < y));
}

}

#endif
