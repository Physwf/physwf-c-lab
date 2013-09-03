#include <iostream>
#include <map>

int main() 
{
	std::map<char,int> mymap;

	mymap.insert(std::pair<char,int>('a',100));
	mymap.insert(std::pair<char,int>('z',200));
	
	std::pair<std::map<char,int>::iterator,bool> ret;
	ret = mymap.insert(std::pair<char,int>('z',500));
	if(ret.second == false)
	{
		std::cout << "element 'z' already exited";
		std::cout << "with a value of" << ret.first->second << '\n';
	}

	std::map<char,int>::iterator it = mymap.begin();
	mymap.insert(it,std::pair<char,int>('b',300));
	mymap.insert(it,std::pair<char,int>('c',400));
	
	std::map<char,int> anothermap;
	anothermap.insert(mymap.begin(),mymap.find('c'));

	std::cout << "mymap contains: \n";
	for(it=mymap.begin();it!=mymap.end();++it)
		std::cout << it->first << "=>" << it->second << '\n';
	std::cout << "another map contains:\n";
	for(it=anothermap.begin();it!=anothermap.end();++it)
		std::cout << it->first << "=>" << it->second << '\n';
	return 0;
}
