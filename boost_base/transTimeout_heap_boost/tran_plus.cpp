
// 模拟状态机超时 并限制每次处理超时状态机的数量

#include <iostream>
#include <boost/heap/fibonacci_heap.hpp>
#include <unordered_map>
#include <chrono>
#include <mutex>
#include <thread>
#include <signal.h>
//#include <memory>

using std::cout;
using std::lock_guard;
using std::mutex;
using std::thread;
using std::unordered_map;
//using std::shared_ptr;

bool flag = false;

const long fsmTimeOutSecond = 10;
const int maxDealNum = 5;

// **事务结构**
struct Transaction
{
    int index;
    std::time_t updateTime;

    // **Boost 堆需要提供比较函数**
    bool operator<(const Transaction &rhs) const
    {
        return updateTime > rhs.updateTime; // `>` 使其成为最小堆
    }
    void clear()
    {
        cout << "clear idx : " << index << "\n";
    }
    ~Transaction()
    {
        cout << "~Transaction idx\n";
    }
};

// **事务管理器**
class TransMan
{
public:
    TransMan() = default;
    ~TransMan() = default;

    void Insert(int index, time_t updateTime);
    void Erase(int index);
    void UpdateTransactionTime(int index, time_t newTime);
    void CheckTimeout();

private:
    mutable mutex my_lock;

    using HeapType = boost::heap::fibonacci_heap<Transaction>;
    HeapType transHeap;

    // handle_type是指向 堆上元素的智能指针  修改 handle_type 关联的值，堆可以自动调整
    unordered_map<int, HeapType::handle_type> indexMap; // 事务索引 -> 堆迭代器
};

// **插入事务**
void TransMan::Insert(int index, time_t updateTime)
{
    lock_guard<mutex> l1(my_lock);
    Transaction t{index, updateTime};
    auto handle = transHeap.push(t); // 插入堆，并获取迭代器
    indexMap[index] = handle;
    cout << "<Insert> idx: " << index << " time: " << updateTime << "\n";
}

// **删除事务**
void TransMan::Erase(int index)
{
    lock_guard<mutex> l1(my_lock);
    auto it = indexMap.find(index);
    Transaction* t = &(*(it->second));
    //shared_ptr<Transaction> t(&(*(it->second)));
    if (it != indexMap.end())
    {
        transHeap.erase(it->second); // **O(logN) 删除堆中的事务**
        indexMap.erase(it);
        t->clear();
        cout << "Erase idx : " << index << " \n";
    }
}

// **更新事务时间**
void TransMan::UpdateTransactionTime(int index, time_t newTime)
{
    lock_guard<mutex> l1(my_lock);
    auto it = indexMap.find(index);
    if (it != indexMap.end())
    {
        Transaction newTrans{index, newTime};
        transHeap.update(it->second, newTrans); // **O(logN) 更新时间**
        cout << "<Update> idx: " << index << " newTime: " << newTime << "\n";
    }
}

// **检查超时事务**
void TransMan::CheckTimeout()
{
    int deal_num = 0;
    lock_guard<mutex> l1(my_lock);
    auto now = std::chrono::system_clock::now();
    auto now_t = std::chrono::system_clock::to_time_t(now);

    while (!transHeap.empty())
    {
        Transaction top = transHeap.top();
        if (now_t - top.updateTime >= fsmTimeOutSecond)
        {
            cout << "Transaction timeout! idx = " << top.index << "\n";
            cout << "send : MAP_ABORT\n";
            transHeap.pop();
            indexMap.erase(top.index);
            // 上面pop、erase操作并没有销毁节点，此时仍然可以调用其中的方法
            top.clear();
        }
        else
            break;

        if (++deal_num >= maxDealNum)
            break;
    }
}

// **定时检查超时事务**
void transactionTimeoutCheckProcess(TransMan *tMan)
{
    while (!::flag)
    {
        tMan->CheckTimeout();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// **创建事务**
void createFsm(TransMan *tMan)
{
    for (int i = 1; i <= 10; ++i)
    {
        auto now = std::chrono::system_clock::now();
        auto now_t = std::chrono::system_clock::to_time_t(now);
        tMan->Insert(i, now_t);

        /*if (i % 3 == 0) // 每 3 个事务后修改 updateTime
        {
            auto new_t = now_t + 5; // 延迟 5 秒
            tMan->UpdateTransactionTime(i, new_t);
        }*/

        if (i > 5)
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
        else
            std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void signalHandle(int i)
{
    ::flag = true;
    cout << "program stop!\n";
}
int main()
{
    TransMan tMan;

    thread t(transactionTimeoutCheckProcess, &tMan);
    thread t1(createFsm, &tMan);
    signal(SIGINT, signalHandle);
    // 睡2s后更新 1 的时间
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto now = std::chrono::system_clock::now();
    auto now_t = std::chrono::system_clock::to_time_t(now);

    tMan.UpdateTransactionTime(1, now_t);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    tMan.Erase(3);
    t.join();
    t1.join();

    cout << "Resource recycling completed \n";
    return 0;
}