#include <string>
#include <iostream>

int main()
{
	using std::string;
	using std::cout;
	using std::endl;
	string st("The expense of spirit\n");
	cout << "The size of " << st << "is " << st.size()
		<< " characters, including the newline" << endl;
	return 0;
}
