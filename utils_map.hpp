#ifndef UTILS_MAP_HPP
# define UTILS_MAP_HPP


#include <iostream>
# include <string>
# include <memory>
# include <limits>
# include <cstddef> // ptrdiff_t
# include <sstream>

static class nullptr_t
{
    public:
        /*
        ** @brief For conversion to any type
        ** of null non-member pointer.
        */
        template<class T>
        operator T*() const { return (0); }

        /*
        ** @brief For conversion to any type of null
        ** member pointer.
        */
        template<class C, class T>
        operator T C::*() const { return (0); }

    private:
        
        /*
        ** @brief It's imposible to get an address of
        ** a nullptr.
        */
        void operator&() const;

} nullptr = {};

#include "rb_tree.hpp"

namespace ft
{
	
template <typename T>
Node<T>	*farRight(Node<T> *node) {
	if (!node)
		return (NULL);
	if (node == node->TNULL)
		return node->TNULL;
	while (node->right != node->TNULL)
	{
		node = node->right;
	}
	return (node);
}

template <typename T>
Node<T>	*farLeft(Node<T> *node) {
	if (!node || node == node->TNULL)
		return node->TNULL;
	while (node->left != node->TNULL)
		node = node->left;
	return (node);
}



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


    template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };

  template <bool is_integral, typename T>
        struct is_integral_res {
            typedef T type;
            static const bool value = is_integral;
            };

    /*
    ** @brief default template of the structure is_integral_type.
    ** If the type given in argument is from the list, the structure
    ** will be overide by nexts, in according to it type.
    ** If the type given is argument isn't in the list, 
    ** stocked value will be false. So it's not a integral type.
    */
    template <typename>
        struct is_integral_type : public is_integral_res<false, bool> {};

    /* @brief is_integral_type for bool. "value is true".*/
    template <>
        struct is_integral_type<bool> : public is_integral_res<true, bool> {};

    /* @brief is_integral_type for char. "value is true".*/
    template <>
        struct is_integral_type<char> : public is_integral_res<true, char> {};

    /* @brief is_integral_type for signed char. "value is true".*/
    template <>
        struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};

    /* @brief is_integral_type for short int. "value is true".*/
    template <>
        struct is_integral_type<short int> : public is_integral_res<true, short int> {};
    
    /* @brief is_integral_type for int. "value is true".*/
    template <>
        struct is_integral_type<int> : public is_integral_res<true, int> {};

    /* @brief is_integral_type for long int. "value is true".*/
    template <>
        struct is_integral_type<long int> : public is_integral_res<true, long int> {};

    /* @brief is_integral_type for long long int. "value is true".*/
    template <>
        struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};

    /* @brief is_integral_type for unsigned char. "value is true".*/
    template <>
        struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};

    /* @brief is_integral_type for unsigned short int. "value is true".*/
    template <>
        struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};

    /* @brief is_integral_type for unsigned int. "value is true".*/
    template <>
        struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};

    /* @brief is_integral_type for unsigned long int. "value is true".*/
    template <>
        struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
    
    /* @brief is_integral_type for unsigned long long int. "value is true".*/
    template <>
        struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

    /*
    ** @brief Give a structure who contain is the
    ** typename given in template is integral or not,
    ** stocked in "value".
    */
    template <typename T>
        struct is_integral : public is_integral_type<T> { };



	template <class T1, class T2>
		struct pair {

			typedef T1		first_type;
			typedef T2		second_type;

			first_type	first;
			second_type	second;

			pair() : first(), second() {}	

			template <class U, class V>
				pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

			pair(const first_type& a, const second_type& b) : first(a), second(b) {}

			pair& operator=(const pair& pr) {
	//			if (*this == pr)
	//				return (*this);
				this->first = pr.first;
				this->second = pr.second;
				return (*this);
			}

		};

		template<class T1, class T2>
		std::ostream&	operator<<(std::ostream& out, const pair<T1, T2>& src)
		{
			out << "first: " << src.first << " second: " << src.second ; 
			return out;
		}


		template <class T1, class T2>
		bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return lhs.first==rhs.first && lhs.second==rhs.second; }

		template <class T1, class T2>
		bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return !(lhs==rhs); }

		template <class T1, class T2>
		bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

		template <class T1, class T2>	
		bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return !(rhs<lhs); }

		template <class T1, class T2>
		bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return rhs<lhs; }

		template <class T1, class T2>
		bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return !(lhs<rhs); }


		template <class T1, class T2>
			ft::pair<T1, T2> make_pair(T1 a, T2 b)
			{
				return (ft::pair<T1, T2>(a, b));
			}

}


#endif
