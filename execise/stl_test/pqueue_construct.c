#include <iostream>
#include <queue>
#include <vector>
#include <functional>

class mycomparison
{
	bool reverse;
public:
	mycomparison(const bool& revparam=false)
	{
		reverse = revparam;
	}
	bool operator()(const int& lhs,const int& rhs) const
	{
		if(reverse) return (lhs>rhs);
		else return (lhs<rhs);
	}
};

int main()
{
	int myints[] = {10,60,50,20};
	std::priority_queue<int> first;
	std::priority_queue<int> second (myints,myints+4);
	std::priority_queue<int,std::vector<int>,std::greater<int> > third(myints,myints+4);

	std::priority_queue<int,std::vector<int>,mycomparison > fourth;

	typedef std::priority_queue<int,std::vector<int>,mycomparison> mypq_type;
	mypq_type fifth(mycomparison());
	mypq_type sixth(mycomparison(true));
	return 0;
}
