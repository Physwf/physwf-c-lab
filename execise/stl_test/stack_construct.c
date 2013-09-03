#include <iostream>
#include <stack>
#include <vector>
#include <deque>

int main()
{
	std::deque<int> mydeque(3,100);
	std::vector<int> myvector(2,200);

	std::stack<int> first;
	std::stack<int> second(mydeque);

	std::stack<int, std::vector<int> > third;
	std::stack<int, std::vector<int> > fourth(myvector);

	std::cout << "size of first:" << first.size() << '\n';
	std::cout << "size of second:" << second.size() << '\n';
	std::cout << "size of third:" << third.size() << '\n';
	std::cout << "size of fourth:" << fourth.size() << '\n';

	return 0;

}
