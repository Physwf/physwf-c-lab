#include <iostream>
#include <vector>

int  main()
{
	std::vector<int> myvector;
	for(int i=0;i<100;i++) myvector.push_back(i);
	
	std::cout << "size:" << (int) myvector.size() << '\n';
	std::cout << "capacity:" << (int) myvector.capacity() << '\n';
	std::cout << "max_size:" << (int) myvector.max_size() << '\n';
	return 0;
}
