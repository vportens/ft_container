#include <list>
#include "../red_black.hpp"
#include "../map.hpp"
#include <iostream>
#include "../utils.hpp"

#define T1 int
#define T2 std::string
typedef ft::pair<const T1, T2> T3;

static int iter = 0;

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param);
//	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_erase(MAP &mp, U param, V param2)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param, param2);
//	printSize(mp);
}

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	ft::map<T1, T2> mp(lst.begin(), lst.end());
//	printSize(mp);
	mp.printmap();
	std::cout << "1" << std::endl;
	ft_erase(mp, ++mp.begin());

	std::cout << "2" << std::endl;
	ft_erase(mp, mp.begin());
	std::cout << "3" << std::endl;
	ft_erase(mp, --mp.end());

	std::cout << "4" << std::endl;
	ft_erase(mp, mp.begin(), ++(++(++mp.begin())));
	std::cout << "5" << std::endl;
	ft_erase(mp, --(--(--mp.end())), --mp.end());

	mp[10] = "Hello";
	mp[11] = "Hi there";
//	printSize(mp);
	std::cout << "6" << std::endl;
	ft_erase(mp, --(--(--mp.end())), mp.end());

	mp[12] = "ONE";
	mp[13] = "TWO";
	mp[14] = "THREE";
	mp[15] = "FOUR";
//	printSize(mp);
	std::cout << "7" << std::endl;
	ft_erase(mp, mp.begin(), mp.end());

	return (0);
}
