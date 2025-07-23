#include <boost/heap/fibonacci_heap.hpp>
#include <iostream>
#include <string>
#include <memory>

using std::shared_ptr;
using std::cout;

class A
{
public:
    A(int num,std::string &name):_x(num),_name(name)
    {
        _py =  new int(2);
        cout << "A() "<< *_py << "\n";
    } 
    ~A()
    {
        delete _py;
        _py = nullptr;
        cout << "~A() \n";
    }
    struct Compare
    {
        bool operator()(const shared_ptr<A> lhs,const shared_ptr<A> rhs) const{
            return lhs->_x < rhs->_x;
        }
    };
    int _x;
    int * _py;
    std::string _name;
};
//using HeapType = boost::heap::fibonacci_heap<A ,boost::heap::compare<A::Compare>>; //for test err
using HeapType = boost::heap::fibonacci_heap<shared_ptr<A> ,boost::heap::compare<A::Compare>>;
void test()
{
    HeapType fHeap;
    //int x = 1;
    std::string temp("a1");
    //A a1(x,temp);
    shared_ptr<A> ptr = std::make_shared<A>(1,temp);
    cout << "before push count:" << ptr.use_count() << "\n";
    auto it1 = fHeap.push(ptr);
    cout << "after push count:" << ptr.use_count() << "\n";
    //A *test = &(*it1);//for test err
    cout << "------------\n";
    fHeap.pop();
    cout << "------------\n";
    cout << "after pop count:" << ptr.use_count() << "\n";
    //test->_x = 666; //for test err
    //*(test->_py) = 777; //for test err
    //cout << "test " << test->_x  << *(test->_py )<< "\n"; //for test err
    //x = 2;
    temp = "a2";
    //A a2(x,temp);
    shared_ptr<A> ptr1 = std::make_shared<A>(2,temp);
    auto it = fHeap.push(ptr1);
    cout << "------------\n";
    fHeap.erase(it);
    cout << "------------\n";
    cout << "after erase count:" << ptr1.use_count() << "\n";
}


int main()
{
    test();
    return 0;
}