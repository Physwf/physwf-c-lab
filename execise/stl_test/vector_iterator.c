#include <iostream>
#include <vector>

int main()
{
	std::vector<int> myvector;
	for(int i=1;i<=5;i++) myvector.push_back(i);

	std::cout << "myvector contains:";
	std::vector<int>::iterator it;
	for(it = myvector.begin();it!=myvector.end();++it)
	{
		std::cout << ' ' << *it;
	}
	std::cout << '\n';
	return 0;
}
