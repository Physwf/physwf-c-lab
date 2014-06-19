#include <time.h>

#include <boost/pool/object_pool.hpp>

 

struct CCC

{

    CCC() {}

    char data[10];

};

 

struct SSS

{

    SSS() {}

    short data[10];

};

 

struct DDD

{

    DDD() {}

    double data[10];

};

 

// 把new,delete封装为一个与boost::object_pool一样的接口，以便于测试

template <typename element_type, typename user_allocator = boost::default_user_allocator_malloc_free>

class new_delete_alloc

{

public:

    element_type* construct() { return new element_type; }

    void destroy(element_type* const chunk) { delete chunk; }

};

 

template

< 

    template<typename, typename>

    class allocator

> 

double test_allocator()

{

    // 使用了一些不规则的分配与释放，增加内存管理的负担

    // 但总体流程还是很规则的，基本上不产生内存碎片，要不然反差效果会更大。

 

    allocator<CCC> c_allc;

    allocator<SSS> s_allc;

    allocator<DDD> d_allc;

 

    double re = 0; // 随便作一些运算，仿止编译器优化掉内存分配的代码

 

    for (unsigned int i = 0; i < 10000; ++i)

    {

        for (unsigned int j = 0; j < 10000; ++j)

        {

            CCC* pc = c_allc.construct();

            SSS* ps = s_allc.construct();

 

            re += pc->data[2];

            c_allc.destroy(pc);

 

            DDD* pd = d_allc.construct();

 

            re += ps->data[2];

            re += pd->data[2];

            s_allc.destroy(ps);

            d_allc.destroy(pd);

        }

    }

 

    return re;

}

 

int main(int argc, char* argv[])

{

    double re1 = 0;

    double re2 = 0;

 

    // 运行内存池测试时，基本上对我机器其它进程没什么影响

    time_t begin = time(0);

    re1 = test_allocator<boost::object_pool>(); // 使用内存池boost::object_pool

    time_t seporator = time(0);

 

 

    // 运行到系统调用测试时，感觉机器明显变慢，

    // 如果再加上内存碎片的考虑，对其它进程的影响会更大。

    std::cout << long(seporator - begin) << std::endl;

    re2 = test_allocator<new_delete_alloc>();           // 直接系统调用

    std::cout << long(time(0) - seporator) << std::endl;

 

    std::cout << re1 << re2 << std::endl;

}