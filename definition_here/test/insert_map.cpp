#include "../red_black.hpp"
#include "../map.hpp"
#include <iostream>
#include "../utils.hpp"

#define T1 int
#define T2 std::string
typedef ft::map<T1, T2>::value_type T3;
typedef ft::map<T1, T2>::iterator iterator;

static int iter = 0;

template <typename MAP, typename U>
void	ft_insert(MAP &mp, U param)
{
	ft::pair<iterator, bool> tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param);
	std::cout << "Created new node: " << tmp.second << std::endl;
}

template <typename MAP, typename U, typename V>
void	ft_insert(MAP &mp, U param, V param2)
{
	iterator tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param, param2);
}

int		main(void)
{
	ft::map<T1, T2> mp, mp2;

	ft_insert(mp, T3(42, "lol"));
	ft_insert(mp, T3(42, "mdr"));

	ft_insert(mp, T3(50, "mdr"));
	ft_insert(mp, T3(35, "funny"));

	ft_insert(mp, T3(45, "bunny"));

	ft_insert(mp, T3(21, "fizz"));
	ft_insert(mp, T3(38, "buzz"));
	mp.printmap();
	mp.erase(mp.begin()++, mp.end());
	mp.printmap();
	iterator cnt = mp.begin();
	int i = 0;
	while (cnt != mp.end())
	{
		std::cout << "index: " << i << "; menbre: " << cnt << std::endl;
		cnt++;
		i++;
	}
	ft_insert(mp, mp.begin(), T3(55, "fuzzy"));

	ft_insert(mp2, mp2.begin(), T3(1337, "beauty"));
	ft_insert(mp2, mp2.end(), T3(1000, "Hello"));
	ft_insert(mp2, mp2.end(), T3(1500, "World"));

	mp2.printmap();

	return (0);
}