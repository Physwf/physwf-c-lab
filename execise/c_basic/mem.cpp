#include <stdio.h>
class A
{
public:
	int id;
	~A();
};

class B
{
	private:
		A *a;
	public:
		void setA(A* v);
		A* getA();
};

A::~A()
{
	printf("~A\n");
}

void B::setA(A *v)
{
	a = v;
	printf("a is set!\n");
}

A * B::getA()
{
	return a;
}

void fun(B *b)
{
	A *a = new A();
	b->setA(a);
	delete a;
}
int main()
{
	B *b = new B();
	//fun(b);
	{
		A *a = new A();
		a->id=123;
		b->setA(a);
	}// p
	printf("id:%d\n",b->getA()->id);
}
