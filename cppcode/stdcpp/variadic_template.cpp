#include <iostream>
#include <functional>
#include <string>

using namespace std;


template<typename Fun, typename ... Args>
void fun(Fun f, Args && ... args) {
    cout << sizeof...(args)<<endl;
    f(std::forward<Args>(args) ... );
}

void foo(int i , int j ) {
    cout<<i <<"+"<<j << endl;
}

void bar(const std::string name) {
    cout << name;
}

int main(int argc, char *argv[])
{
//    cout << "Hello World!" << endl;

    fun(foo, 4, 5);
    fun(bar,std::string("str"));

    return 0;
}
