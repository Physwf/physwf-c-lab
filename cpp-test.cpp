#.在32位机器上，有如下代码：

char array[] = "abcdefg";
printf("%d\n",sizeof(array)); // 8

char *p = "abcdefg";
printf("%d\n",sizeof(p)); // 4

void func(char p[10])
{
	printf("%d\n",sizeof(p)); // 4
}

void func(char (&p)[10])
{
	printf("%d\n",sizeof(p)); // 10
}

int main(void)
{
	printf("%d\n",sizeof(char[2])); // 2
	printf("%d\n",sizeof(char&)); // 1
	return 0;
}

  其输出结果依次为：
　　A、8 4 4 10 2 1
　　B、4 4 4 10 4 1
　　C、8 4 4 10 2 4
　　D、8 4 4 4 2 1
　　E、8 4 4 10 4 4
　　F、以上答案都不对

#.CONTAINER::iterator iter , tempIt;
for(iter = cont.begin() ; iter != cont.end() ; )
{
	tempIt = iter;
	++iter;
	cont.erase(tempIt);
}
　　假设cont是一个CONTAINER的示例，里面包含数个元素，那么当CONTAINER为：
　　1、vector
　　2、list
　　3、map
　　4、deque
　　会导致上面的代码片段崩溃的CONTAINER类型是：
　　A、1，4 B、2，3 C、1，3 D、2，4
　　正确答案选择A(第1个、第4个都是线性的类型存储，所以会存在崩溃)

#.以下代码
class classA
{
public:
	classA()
	{
		clear();
	}

	virtual ~classA()
	{

	}

	void clear()
	{
		memset(this, 0, sizeof(*this));
	}

	virtual void func()
	{
		printf("func\n");
	}
};

class classB : public classA
{

};
int main(void)

{
	classA oa;
	classB ob;
	classA * pa0 = &oa;
	classA * pa1 = &ob;
	classB * pb = &ob;
	oa.func();          /* 1 */
	ob.func();          /* 2 */
	pa0->func();        /* 3 */
	pa1->func();        /* 4 */
	pb->func();         /* 5 */
	return(0);
}
　　A、func func 执行出错 执行出错 func
　　B、执行出错 func 执行出错 执行出错 func
　　C、执行出错 执行出错 执行出错 执行出错 执行出错
　　D、func func func func func
　　E、func func 执行出错 func func
　　F、以上选项都不对

#.在32位系统中
class CBase
{
public:
	void func()
	{
		Print();
	}
	virtual void Print()
	{
		cout << "CBase::Print" <
	}
};
class CDerived : public CBase
{
public:
	virtual void Print()
	{
		cout << "CDerived::Print" <
	}
};
int main(void)
{
	CDerived c;
	CBase *p = &c;
	return 0;
}
请问：
sizeof(*p)的值是多少 ? (实际上求的就是一个成员变量的大小 + 一个虚表指针VPTR的大小)
A、1 B、4 C、8 D、12
p->Print(); 和 c.func(); 的输出分别是 ?
A、CBase::Print CBase::Print B、CBase::Print CDerived::Print
C、CDerived::Print CBase::Print D、CDerived::Print CDerived::Print

#.
struct Thing
{
	int valueA;
	const int valueB;
};
Thing t;
t的成员变量valueA 和 valueB 的值分别为：
A、0 0 B、垃圾值 0 C、无法运行 D、垃圾值 垃圾值
常成员变量valueB必须在构造函数中进行初始化

#.for(int x = 0 , y = 0; !x && y <= 5 ; y++)语句执行循环的次数是：
　　A、0 B、5 C、6 D、无数次

#.在Windows 32位操作系统中，假设字节对齐为4，对于一个空的类A，sizeof(A)的值为()
　　A、0 B、1 C、2 D、4

#.以下对函数指针的定义，哪些是正确的：
　　A、typedef int (*fun_ptr)(int , int); B、typedef int *(fun_ptr)(int , int);
　　C、typedef int (fun_ptr*)(int , int); D、typedef *int (fun_ptr)(int , int);

#.在32位系统中，下面结构体
struct st
{
	char ch, *ptr;
	union
	{
		short a, b;
		unsigned int c : 2, d : 1;
	};
	bool f;
	struct st *next;
};
的大小是：
A、14字节 B、16字节 C、20字节 D、24字节

11、32位小端字节序的机器上，如下代码：
char array[12] = {0x01 , 0x02 , 0x03 , 0x04 , 0x05 , 0x06 , 0x07 , 0x08};
short *pshort = (short *)array;
int *pint = (int *)array;
int64 *pint64 = (int64 *)array;
printf("0x%x , 0x%x , 0x%x , 0x%x", *pshort , *(pshort+2) , *pint64 , *(pint+2));
　　输出结果为：
　　A、0x201 , 0x403 , 0x807060504030201 , 0x0 B、0x201 , 0x605 , 0x807060504030201 , 0x0
　　C、0x201 , 0x605 , 0x4030201 , 0x8070605 D、0x102 , 0x506 , 0x102030405060708 , 0x0
　　E、0x102 , 0x304 , 0x1020304 , 0x5060708 F、0x201 , 0x605 , 0x4030201 , 0x6050403

#.有关引用，下列说法错误的是：
　　A、引用定义时必须初始化
　　B、类的非静态引用成员变量不需要在构造函数中初始化
　　C、数组可以有引用，但没有引用数组
　　D、public派生对象可以初始化基类类型的引用
　　E、整型数据的常引用可以直接用数值初始化
　　F、以上选项都不是
#.Windows PE文件装载到的地址为：
　　A、0x0030000 B、0x0040000 C、任意地址 D、0x10000000
#.以下哪些对象可用于Windows进程间通信：
　　A、事件 B、临界区 C、互斥量 D、共享内存