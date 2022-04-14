#ifndef BASE_CLASS_HPP
# define BASE_CLASS_HPP



# include <iostream>
# include <string>
# include <memory>
# include <limits>
# include <cstddef> // ptrdiff_t
# include <sstream> // ostring
# include "utils.hpp"
namespace ft {


// Relational Operators Comparison Functions

template <class Ite1, class Ite2>
bool	equal(Ite1 first1, Ite1 last1, Ite2 first2)
{
	while (first1 != last1)
	{
		if (*first1 != *first2)
			return false;
		++first1; ++first2;
	}
	return true;
}

// Ite len

template <class Ite>
size_t	itlen(Ite first, Ite last) {
	size_t	i = 0;

	while (first != last)
	{
		++first;
		++i;
	}
	return (i);
}

// true if the first range compares lexicographically less than the second.
// false otherwise (including when all the elements of both ranges are equivalent).

template <class Ite1, class Ite2>
bool	lexicographical_compare(Ite1 first1, Ite1 last1, Ite2 first2, Ite2 last2)
{
	while (first1 != last1 && first2 != last2 && *first1 == *first2)
	{
		++first1; ++first2;
	}
	if (first1 == last1)
		return (first2 != last2);
	else if (first2 == last2)
		return (false);
	return (*first1 < *first2);
}

/*
template <typename T>
struct	lstNode
{
	T			data;
	lstNode		*next;
	lstNode		*prev;

	lstNode(const T &src = T()) : data(src), next(this), prev(this) {};
};

template <typename T>
struct	mapNode
{
	private:
	bool _unused;


	public:
	T			data;
	mapNode		*parent;
	mapNode		*left;
	mapNode		*right;

	mapNode(const T &src = T()) : \
		data(src), parent(NULL), left(NULL), right(NULL) {};
};
*/

template <typename T>
mapNode<T>	*farRight(mapNode<T> *node) {
	while (node->right != NULL)
		node = node->right;
	return (node);
}

template <typename T>
mapNode<T>	*farLeft(mapNode<T> *node) {
	while (node->left != NULL)
		node = node->left;
	return (node);
}



} // ******************************************************* ft namespace end //

#endif // ************************************************ BASE_CLASS_HPP end //