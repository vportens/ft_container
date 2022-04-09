#include "noob/map.hpp"
#include <list>

#define T1 int
#define T2 std::string
typedef ft::pair<const T1, T2> T3;

static int iter = 0;

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "value to delete: " << param << std::endl;
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "ret: " << mp.erase(param) << std::endl;
	mp.printTree();
}

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 6;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	ft::map<T1, T2> mp(lst.begin(), lst.end());
	mp.printTree();

	std::cout << "first befor any erase" << std::endl;
	mp.printTree();
	for (int i = 2; i < 4; ++i)
	{
		std::cout << "tree print:" << std::endl;
		mp.printTree();
		ft_erase(mp, i);
	}

	std::cout << "test" << std::endl;
	mp.printTree();
	ft_erase(mp, mp.begin()->first);
	std::cout << "test1" << std::endl;
	mp.printTree();
	ft_erase(mp, (--mp.end())->first);
	std::cout << "test2" << std::endl;
	mp.printTree();

	mp[-1] = "Hello";
	std::cout << "test3" << std::endl;
	mp.printTree();
	std::cout << "test3.2" << std::endl;
	mp[10] = "Hi there";
	std::cout << "test4" << std::endl;
	mp.printTree();
	mp[10] = "Hi there";
	std::cout << "test5" << std::endl;
	mp.printTree();

	ft_erase(mp, 0);
	std::cout << "test6" << std::endl;
	ft_erase(mp, 1);
	std::cout << "test7" << std::endl;

	return (0);
}
