#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class IEvent
{
public:
    virtual void Test1(int i) = 0;
    virtual void Test2(int i) = 0;
    virtual void Test3(int i) = 0;
};
class TestEvent:public IEvent
{
public:
    void Test1(int i) { cout << "Test11 : " << i << endl;}
    void Test2(int i) { cout << "Test12 : " << i << endl;}
    void Test3(int i) { cout << "Test13 : " << i << endl;}
private:
    int p;
};
class TestEvent1:public IEvent
{
public:
    void Test1(int i) { cout << "Test21 : " << i << endl;}
    void Test2(int i) { cout << "Test22 : " << i << endl;}
    void Test3(int i) { cout << "Test23 : " << i << endl;}
private:
    int p;
};
class NotifyEvent
{
public:
    void Run(int flag)
    {
        switch(flag)
        {
            case 1:
                testEvent_->Test1(1);
                break;
            case 2:
                testEvent_->Test2(2);
                break;
            case 3:
                testEvent_->Test3(3);
                break;
            default:
                break;
        }
    }
    void SetMyEvent(IEvent* testEvent) {testEvent_ = testEvent;}
private:
    IEvent* testEvent_;
};
int main() {
    IEvent* ptr_event = new TestEvent;
    NotifyEvent notifyEvent;
    notifyEvent.SetMyEvent(ptr_event);
    notifyEvent.Run(1);
    notifyEvent.Run(3);
    ptr_event = new TestEvent1;
    notifyEvent.SetMyEvent(ptr_event);
    notifyEvent.Run(1);
    notifyEvent.Run(3);
    return 0;
}