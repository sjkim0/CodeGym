#include <iostream>

using namespace std;



template<typename T>
class TestClass
{
private:
    T data;

public:
// 생성자, c#보다 더 나은것 같기도하고흠
    TestClass(T data) : data(data)
    {
        cout << data;
    }
};
/*
    template는 다음 semicolumn까지로 range가 정해지는것으로보임
*/
template<typename W>
class templateTest
{
    private:
    T data;
    public: 
};

int main()
{
    TestClass<int> myClass(42);
    TestClass<int> *pMyClass = new TestClass<int>(1234);

    delete pMyClass;

    return 0;
}