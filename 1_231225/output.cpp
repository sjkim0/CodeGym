#include <iostream>

using namespace std;



template<typename T>
class TestClass
{
private:
    T data;

public:
    TestClass(T data) : data(data)
    {
        cout << data;
    }
};

int main()
{
    TestClass<int> myClass(42);
    TestClass<int> *pMyClass = new TestClass<int>(1234);

    delete pMyClass;
    
    return 0;
}